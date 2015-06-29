#ifndef _ORCAACTION_CREATEESTIMATE_H
#define _ORCAACTION_CREATEESTIMATE_H

#include <SQLiteCpp/Statement.h>
#include "../OrcaAction.h"

namespace action
{
class InsertEstimate : public OrcaAction
{
public:
    InsertEstimate(int budgetId):_budgetId(budgetId) {}
    virtual ~InsertEstimate() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "INSERT INTO estimate(budget_id, amount, category_id)"
                     "  VALUES (?1, 0, (SELECT max(category_id) FROM category))";
        SQLite::Statement stm(database, query);
        stm.bind(1, _budgetId  );
        if(!stm.exec()) {
            throw std::runtime_error("Unknown error");
        }
    }
private:
    int _budgetId;
};
}


#endif // _ORCAACTION_CREATEESTIMATE_H

