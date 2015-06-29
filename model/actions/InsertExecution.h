#ifndef _ORCAACTION_EXECUTION_H
#define _ORCAACTION_EXECUTION_H

#include <SQLiteCpp/Statement.h>
#include "../OrcaAction.h"

namespace action
{
class InsertExecution : public OrcaAction
{
public:
    InsertExecution(int estimateId, int walletId):
        _estimateId(estimateId), _walletId(walletId) {}
    virtual ~InsertExecution() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "INSERT INTO execution(estimate_id, wallet_id, amount)"
                     "  VALUES (?1, ?2, 0)";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId);
        stm.bind(2, _walletId);
        if(!stm.exec()) {
            throw std::runtime_error("Unknown error");
        }
    }
private:
    int _estimateId;
    int _walletId;
};
}

#endif // _ORCAACTION_EXECUTION_H

