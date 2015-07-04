#include "EstimatePlaningView.h"

static auto sql = R"=(
SELECT estimate_id, prom.name, DATE(bud.start, prom.due),
    prom.amount/100.0,
    cat.name, prom.obs
  FROM budget bud
  JOIN estimate prom USING(budget_id)
  LEFT JOIN category cat USING(category_id)
  WHERE budget_id = ?1
  ORDER BY category_id, prom.name;
)=";

EstimatePlaningView::EstimatePlaningView():
    OrcaView(sql)
{
    //ctor
}

void EstimatePlaningView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _budgetId);
}
void EstimatePlaningView::search(const Search& s)
{
}

