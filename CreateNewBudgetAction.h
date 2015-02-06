#ifndef CREATENEWBUDGETACTION_H
#define CREATENEWBUDGETACTION_H

#include "OrcaAction.h"


class CreateNewBudgetAction : public OrcaAction
{
public:
    CreateNewBudgetAction() {}
    virtual ~CreateNewBudgetAction() {}
protected:
    virtual void doAction(SQLite::Database &database) override
    {
        if(!_document->_model.exec("INSERT INTO budget(name, start, duration) "
                             "  SELECT strftime('%m/%Y', start, duration), date(start, duration), duration "
                             "    FROM budget WHERE budget_id IN (SELECT max(budget_id) FROM budget)")
        ){
            wxMessageBox("The total universe time expired :(");
        }
    }
private:
};

#endif // CREATENEWBUDGETACTION_H
