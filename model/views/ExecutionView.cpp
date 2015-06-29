#include "ExecutionView.h"

static auto sql = R"=(
SELECT execution_id, amount/100.0, "date",
    wallet.name, description, execution.obs
FROM execution JOIN wallet USING(wallet_id)
WHERE estimate_id = ?1
)=";

ExecutionView::ExecutionView():
    OrcaView(sql)
{
    //ctor
}

void ExecutionView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _estimateId);
}

