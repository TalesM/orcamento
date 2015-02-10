#ifndef _ORCAACTION_DELETEESTIMATE_H
#define _ORCAACTION_DELETEESTIMATE_H

#include <SQLiteCpp/Statement.h>
#include "../OrcaAction.h"

namespace action
{
class DeleteEstimate : public OrcaAction
{
public:
    DeleteEstimate(int estimateId):_estimateId(estimateId) {}
    virtual ~DeleteEstimate() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "DELETE FROM estimate WHERE estimate_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId  );
        if(!stm.exec()) {
            throw std::runtime_error("Estimate not found.");
        }
    }
private:
    int _estimateId;
};
}


#endif // _ORCAACTION_DELETEESTIMATE_H

