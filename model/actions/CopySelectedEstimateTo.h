#ifndef _ORCAACTION_COPYSELECTEDESTIMATETO_H
#define _ORCAACTION_COPYSELECTEDESTIMATETO_H

#include <SQLiteCpp/Statement.h>
#include "../OrcaAction.h"

namespace action
{
class CopySelectedEstimateTo : public OrcaAction
{
public:
    CopySelectedEstimateTo(int estimateId, int increment):
        _estimateId(estimateId),
        _increment(increment)
    {}
    virtual ~CopySelectedEstimateTo() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "INSERT OR REPLACE INTO estimate(budget_id, category_id,name, amount, due, obs)"
                     "  SELECT budget_id + ?2, category_id, name, amount, due, obs"
                     "    FROM estimate "
                     "    WHERE category_id IS NOT NULL "
                     "      AND name IS NOT NULL "
                     "      AND estimate_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId  );
        stm.bind(2, _increment  );
        if(!stm.exec()) {
            throw std::runtime_error("Estimate not found.");
        }
    }
private:
    int _estimateId;
    int _increment;
};
}
#endif // _ORCAACTION_COPYSELECTEDESTIMATETO_H
