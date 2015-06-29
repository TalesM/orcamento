#include "BudgetView.h"

static auto sql = R"=(
SELECT budget_id, name, executing, budget_id IN (
   SELECT max(budget_id)FROM budget WHERE budget.executing=1
)
FROM budget ORDER BY budget_id
)=";

BudgetView::BudgetView():
    OrcaView(sql)
{

}

