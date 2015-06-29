#include "ExecutionSummaryView.h"

static auto sql = R"=(
SELECT budget.name, estimate.name, estimate.amount/100.0,
    IFNULL(SUM(execution.amount), 0)/100.0,
    (IFNULL(SUM(execution.amount), 0) - estimate.amount)/100.0,
    COUNT(execution_id)
FROM estimate JOIN budget USING(budget_id)
LEFT JOIN execution USING(estimate_id)
WHERE estimate_id = ?1
)=";

ExecutionSummaryView::ExecutionSummaryView():
    OrcaView(sql)
{
    //ctor
}

void ExecutionSummaryView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _estimateId);
}
