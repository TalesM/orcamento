#include "EstimateExecutingView.h"

static auto sql = R"=(
SELECT estimate_id, prom.name, DATE(bud.start, prom.due),
    prom.amount/100.0, SUM(exc.amount)/100.0,
    (IFNULL(SUM(exc.amount), 0)-prom.amount)/100.0,
    cat.name, prom.obs
  FROM budget bud
  JOIN estimate prom USING(budget_id)
  LEFT JOIN category cat USING(category_id)
  LEFT JOIN execution exc USING(estimate_id)
  WHERE budget_id = ?1
  GROUP BY estimate_id
  ORDER BY category_id, prom.name;
)=";

EstimateExecutingView::EstimateExecutingView():
    OrcaView(sql)
{
    //ctor
}
void EstimateExecutingView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _budgetId);
}
