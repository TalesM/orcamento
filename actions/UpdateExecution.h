#ifndef _ORCAACTION_UPDATEEXECUTION_H
#define _ORCAACTION_UPDATEEXECUTION_H

#include <SQLiteCpp/Statement.h>
#include <string>
#include <sstream>
#include "../OrcaAction.h"

namespace action
{

template <typename VAL>
class UpdateExecutionBase: public OrcaAction
{
public:
    UpdateExecutionBase(int executionId, const VAL &v):
        _executionId(executionId),
        _value(v) {}

protected:
    void doAction(SQLite::Database &database, const std::string &field) const
    {
        auto query = "UPDATE execution SET \""+field+"\" = ?2 WHERE execution_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _executionId  );
        stm.bind(2, _value);
        if(!stm.exec()) {
            throw std::runtime_error("Invalid estimate or field name.");
        }
    }
private:
    int _executionId;
    VAL _value;
};

/**
 * @brief Changes the amount.
 */
class UpdateExecutionAmount: public UpdateExecutionBase<int>
{
public:
    UpdateExecutionAmount(int executionId, double v): UpdateExecutionBase<int>(executionId, round(v*100)) {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        UpdateExecutionBase<int>::doAction(database, "amount");
    }
};

}

#endif // _ORCAACTION_UPDATEEXECUTION_H
