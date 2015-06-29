#ifndef _ORCAACTION_EXECUTENEXTBUDGET_H
#define _ORCAACTION_EXECUTENEXTBUDGET_H

#include "../OrcaAction.h"

namespace action
{
class ExecuteNextBudget : public OrcaAction
{
public:
    ExecuteNextBudget() {}
    virtual ~ExecuteNextBudget() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        if(!database.exec("UPDATE budget SET executing = 1"
                          "  WHERE budget_id IN (SELECT min(budget_id)"
                          "  FROM budget WHERE executing=0)")
          ) {
            throw std::runtime_error("There is no budget plan remaining.");
        }
    }
private:
};
}


#endif // _ORCAACTION_EXECUTENEXTBUDGET_H

