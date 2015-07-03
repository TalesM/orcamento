#include "TotalsView.h"

static auto sql = R"=(
SELECT
    budget.name,
    SUM(fixed_estimate.estimated)/100.0,
    SUM(fixed_estimate.accounted)/100.0,
    (SUM(fixed_estimate.accounted) - SUM(fixed_estimate.estimated))/100.0
FROM budget
JOIN (
    SELECT CASE WHEN ABS(execution_estimate.amount) > ABS(estimate.amount)
            THEN execution_estimate.amount
            ELSE estimate.amount
        END AS estimated,
        execution_estimate.amount AS accounted, 
        budget_id,
        estimate.name AS name
    FROM estimate
        LEFT JOIN (
            SELECT
                IFNULL(SUM(execution.amount), 0) AS amount, estimate_id
            FROM execution GROUP BY estimate_id
        ) AS execution_estimate USING(estimate_id)
) AS fixed_estimate USING(budget_id)
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
    for(size_t i = 0; i < _params.sValues.size(); ++i){
        std::stringstream ss;
        ss << ":s_" << (i+1);
        stm.bind(ss.str(), _params.sValues[i]);
    }
}
void TotalsView::search(const Search& search)
{
    if(!search){
        _params = SearchQuery{};
        return query(sql);
    }
    _params = sqlize(search, {{"name", "fixed_estimate.name"}});
    query(std::string(sql) + " AND " + _params.query);
}

