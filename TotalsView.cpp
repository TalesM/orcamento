#include "TotalsView.h"

static auto sql = R"=(
SELECT
  budget.name,
  SUM(estimate.amount)/100.0,
  SUM(execution_estimate.amount)/100.0,
  (SUM(execution_estimate.amount) - SUM(estimate.amount))/100.0
FROM budget
JOIN estimate USING(budget_id)
LEFT JOIN (SELECT
    IFNULL(SUM(execution.amount), 0) AS amount,
    estimate_id
  FROM execution GROUP BY estimate_id
) execution_estimate USING(estimate_id)
WHERE budget_id = ?1
)=";

TotalsView::TotalsView():
    OrcaView(sql)
{
    //ctor
}

void TotalsView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _budgetId);
}

