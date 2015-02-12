#include "OrcaDocument.h"
#include <stdexcept>

OrcaDocument::OrcaDocument(const std::string &path, bool erase):
    _model(path, SQLITE_OPEN_READWRITE|(erase?SQLITE_OPEN_CREATE:0))
{
}

std::unique_ptr<OrcaDocument> OrcaDocument::create(const std::string &path, const wxDateTime& start)
{
    auto newDocument = std::make_unique<OrcaDocument>(path, true);
    wxFile modelFile(L"theModel.sql");
    wxString model;
    if(modelFile.ReadAll(&model)){
        throw std::runtime_error("Can't find config file \"theModel.sql\".");
    }
    SQLite::Transaction transaction(newDocument->_model);
    newDocument->_model.exec(model.ToUTF8());

    auto query = "INSERT INTO budget(name, start, duration)"
                 "  VALUES (strftime('%m/%Y', ?1), date(?1, 'start of month'), '1 months')";
    SQLite::Statement stm(newDocument->_model, query);
    stm.bind(1, start.FormatISODate().ToUTF8());
    stm.exec();

    // Commit transaction
    transaction.commit();
    return newDocument;
}
std::unique_ptr<OrcaDocument> OrcaDocument::load(const std::string& path)
{
    return std::make_unique<OrcaDocument>(path, true);
}


OrcaDocument::~OrcaDocument()
{
    //Check if saved
}

void OrcaDocument::save()
{
    if(_transaction){
        _transaction->commit();
        _transaction.reset();
    }
}


std::unique_ptr<SQLite::Transaction> &OrcaDocument::transaction()
{
    if(!_transaction){
        _transaction = std::make_unique<SQLite::Transaction>(_model);
    }
    return _transaction;
}
