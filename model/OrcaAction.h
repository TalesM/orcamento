#ifndef _ORCAACTION_H
#define _ORCAACTION_H

#include <stdexcept>
#include <string>
#include <typeinfo>
#include <SQLiteCpp/Database.h>

class CanNotUndo: public std::runtime_error
{
public:
    CanNotUndo(const std::string &s): std::runtime_error(s) {}
};

/**
 * @brief base class for actions.
 */
class OrcaAction
{
public:
    OrcaAction() {}
    virtual ~OrcaAction() {}
protected:
    virtual void doAction(SQLite::Database &database) const = 0 ;
    virtual void undoAction(SQLite::Database &database) const
    {
        throw CanNotUndo(typeid(*this).name());
    }
private:
    friend class OrcaDocument;
};

#endif // _ORCAACTION_H
