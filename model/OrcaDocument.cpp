#include "OrcaDocument.h"
#include "sql/create_0_4_0.h"
#include "conversor.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <streambuf>
#include <vector>

OrcaDocument::OrcaDocument(const std::string &path, bool erase):
    _model(path, SQLITE_OPEN_READWRITE|(erase?SQLITE_OPEN_CREATE:0))
{
    if(erase){
        return;
    }
    std::string s = _model.execAndGet("SELECT \"value\" FROM \"meta\" WHERE \"key\"='format-version'");
    std::vector<int> versionArray;
    size_t p = 0, q = 0;
    do{
        p = s.find('.', q);
        versionArray.push_back(atoi(s.substr(q, p).c_str()));
        q = p+1;
    }while(p != std::string::npos);
    if(versionArray.size() < 3){
        throw std::runtime_error("String Version formated incorrectly.");
    }
    
    if(versionArray[0] != fileFormat::MAJOR || versionArray[1] != fileFormat::MINOR || versionArray[2] != fileFormat::PATCH || (versionArray.size()>3 && versionArray[3] < fileFormat::VARIANT)){
        transaction();
        if(not upgrade(_model, versionArray, {fileFormat::MAJOR, fileFormat::MINOR, fileFormat::PATCH, fileFormat::PATCH})){
            throw wrongver_error(versionArray[0], versionArray[1], versionArray[2], (versionArray.size()>3)?(versionArray[3]):0);
        }
    }
}

static std::string readModel(){
    return v0_4_0::createScript;
}

std::unique_ptr<OrcaDocument> OrcaDocument::create(const std::string &path, const std::string& start)
{
    auto newDocument = std::make_unique<OrcaDocument>(path, true);
    std::string model = readModel();
    SQLite::Transaction transaction(newDocument->_model);
    newDocument->_model.exec(model);

    auto query = "INSERT INTO budget(name, start, duration)"
                 "  VALUES (strftime('%m/%Y', ?1), date(?1, 'start of month'), '1 months')";
    SQLite::Statement stm(newDocument->_model, query);
    stm.bind(1, start);
    stm.exec();

    // Commit transaction
    transaction.commit();
    return newDocument;
}
std::unique_ptr<OrcaDocument> OrcaDocument::load(const std::string& path)
{
    return std::make_unique<OrcaDocument>(path, false);
}

bool OrcaDocument::canConvert(int major, int minor, int patch, int variant)
{
    return (major == 0 && minor == 1);
}

std::unique_ptr<OrcaDocument> OrcaDocument::convertFrom0_1_0(const std::string &opath, const std::string &npath)
{
    auto newDocument = std::make_unique<OrcaDocument>(npath, true);
    newDocument->_model.exec(readModel());
    newDocument->_model.exec("ATTACH DATABASE '"+opath+"' AS oldData");
    const char conversor[] =
"REPLACE INTO main.wallet SELECT * FROM oldData.wallet;"
"REPLACE INTO main.budget SELECT * FROM oldData.budget;"
"REPLACE INTO main.category SELECT * FROM oldData.category;"
"INSERT INTO main.estimate SELECT * FROM oldData.estimate WHERE category_id IS NOT NULL;"
"INSERT INTO main.execution SELECT * FROM oldData.execution WHERE estimate_id IN ("
"    SELECT estimate_id FROM oldData.estimate WHERE category_id IS NOT NULL"
");";
    newDocument->_model.exec(conversor);
    newDocument->_model.exec("DETACH DATABASE oldData");
    return newDocument;
}



OrcaDocument::~OrcaDocument()
{
    //Check if saved
}

int OrcaDocument::doAction(std::unique_ptr<OrcaAction> action)
{
    transaction();
    _model.exec("SAVEPOINT actionBasic");
    action->doAction(_model);
    _doneActions.push_back(std::move(action));
    _undoneActions.clear();
    return _model.getLastInsertRowid();
}

bool OrcaDocument::undo()
{
    if(_doneActions.empty()){
        return false;
    }
    _model.exec("ROLLBACK TO actionBasic;");
    _undoneActions.push_back(std::move(_doneActions.back()));
    _doneActions.pop_back();
    if(_doneActions.empty()){
        _transaction.reset();
    }
    return true;
}

bool OrcaDocument::redo()
{
    if(_undoneActions.empty()){
        return false;
    }
    transaction();
    _model.exec("SAVEPOINT actionBasic");
    auto action = std::move(_undoneActions.back());
    _undoneActions.pop_back();
    action->doAction(_model);
    _doneActions.push_back(std::move(action));
    return true;
}

void OrcaDocument::save()
{
    if(_transaction){
        _transaction->commit();
        _transaction.reset();
        _doneActions.clear();
        _undoneActions.clear();
    }
}


std::unique_ptr<SQLite::Transaction> &OrcaDocument::transaction()
{
    if(!_transaction){
        _transaction = std::make_unique<SQLite::Transaction>(_model);
    }
    return _transaction;
}
