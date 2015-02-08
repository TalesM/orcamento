#ifndef CREATENEWBUDGETACTION_H
#define CREATENEWBUDGETACTION_H

#include "OrcaAction.h"

namespace action
{
class CreateNewBudget : public OrcaAction
{
public:
    CreateNewBudget() {}
    virtual ~CreateNewBudget() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        if(!database.exec("INSERT INTO budget(name, start, duration) "
                          "  SELECT strftime('%m/%Y', start, duration), date(start, duration), duration "
                          "    FROM budget WHERE budget_id IN (SELECT max(budget_id) FROM budget)")
          ) {
            throw std::runtime_error("The total universe time expired :(");
        }
    }
private:
};
}

#endif // CREATENEWBUDGETACTION_H
