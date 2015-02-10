#include "BudgetToCopyView.h"

static auto sql = R"=(
SELECT name
 FROM budget
 WHERE budget_id > ?1
 ORDER BY budget_id ASC
)=";

BudgetToCopyView::BudgetToCopyView():
    OrcaView(sql)
{
    //ctor
}

void BudgetToCopyView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _sourceBudgetId);
}
