#include "TotalsView.h"

static auto _sql = R"=(
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
        estimate.name AS name,
        estimate.obs AS obs,
        estimate.due AS due,
        estimate.category_id
    FROM estimate
        LEFT JOIN (
            SELECT
                IFNULL(SUM(execution.amount), 0) AS amount, estimate_id
            FROM execution 
            {{sub}}
            
            
            GROUP BY estimate_id
        ) AS execution_estimate USING(estimate_id)
) AS fixed_estimate USING(budget_id)
WHERE budget_id = :budget
)=";

std::string sql(const std::string &mainQuery="", const std::string &execQuery="");

TotalsView::TotalsView():
    OrcaView(sql())
{
    //ctor
}

void TotalsView::setup(SQLite::Statement& stm)
{
    stm.bind(":budget", _budgetId);
    for(size_t i = 0; i < _sValues.size(); ++i){
        std::stringstream ss;
        ss << ":s_" << (i+1);
        stm.bind(ss.str(), _sValues[i]);
    }
    for(size_t i = 0; i < _iValues.size(); ++i){
        std::stringstream ss;
        ss << ":i_" << (i+1);
        stm.bind(ss.str(), _iValues[i]);
    }
}
void TotalsView::search(const Search& search)
{
    if(!search){
        _sValues.clear();
        _iValues.clear();
        return query(sql());
    }
    auto params = sqlize(search, { 
        { "name", "fixed_estimate.name" },
        { "obs", "fixed_estimate.obs" },
        { "estimated", "(fixed_estimate.estimated)", FieldDescriptor::MONEY },
        { "accounted", "(fixed_estimate.accounted)", FieldDescriptor::MONEY },
        { "remaining", "((fixed_estimate.accounted-fixed_estimate.estimated))", FieldDescriptor::MONEY },
        { "due", "CAST(STRFTIME('%d', \"start\", due) AS INTEGER)", FieldDescriptor::INT },
        { "category", "category_id", FieldDescriptor::INT },
    });
    auto subParams = sqlize(search, {{"wallet", "wallet_id", FieldDescriptor::INT}}, std::make_pair(params.sValues.size(), params.iValues.size()));
    
    query(std::string(sql(params.query, subParams.query)));
    _sValues = std::move(params.sValues);
    _sValues.insert(_sValues.end(), subParams.sValues.begin(), subParams.sValues.end());
    _iValues = std::move(params.iValues);
    _iValues.insert(_iValues.end(), subParams.iValues.begin(), subParams.iValues.end());
}

std::string sql(const std::string &mainQuery, const std::string &execQuery){
    auto subQuery = [&execQuery](const std::string &_sql){
        std::string s = _sql;
        const char sub[] = "{{sub}}";
        auto i = s.find(sub);
        if(execQuery.size()){
            return s.replace(i, sizeof(sub), "WHERE "+execQuery);
        }
        return s.replace(i, sizeof(sub), "");
    };
    if(mainQuery.size()){
        return subQuery(_sql) + " AND " + mainQuery;
    }
    return subQuery(_sql);
}
