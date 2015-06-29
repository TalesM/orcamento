#ifndef _ORCAACTION_DELETEEXECUTION_H
#define _ORCAACTION_DELETEEXECUTION_H

#include <SQLiteCpp/Statement.h>
#include "../OrcaAction.h"

namespace action
{
class DeleteExecution : public OrcaAction
{
public:
    DeleteExecution(int executionId):_executionId(executionId) {}
    virtual ~DeleteExecution() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "DELETE FROM execution WHERE execution_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _executionId);
        if(!stm.exec()) {
            throw std::runtime_error("Execution not found.");
        }
    }
private:
    int _executionId;
};
}

#endif // _ORCAACTION_DELETEEXECUTION_H

