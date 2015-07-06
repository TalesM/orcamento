#include "EstimateExecutingView.h"

static auto _sql = R"=(
SELECT 
    estim.estimate_id,
    estim.name AS name,
    STRFTIME("%d", bud.start, estim.due) AS due,
    estim.amount/100.0 AS estimated,
    exc.amount/100.0 AS accounted, 
    (IFNULL(exc.amount, 0)-estim.amount)/100.0 AS remaining,
    cat.name AS category, 
    estim.obs AS obs
FROM budget bud
    JOIN estimate estim USING(budget_id)
    LEFT JOIN category cat USING(category_id)
    LEFT JOIN (
        SELECT
            IFNULL(SUM(execution.amount), 0) AS amount, estimate_id
        FROM execution 
        {{sub}}
        GROUP BY estimate_id
    ) AS exc USING(estimate_id)
    WHERE budget_id = :budget {{main}}
    ORDER BY category_id, estim.name
)=";


static std::string sql(const std::string &mainQuery="", const std::string &execQuery="");

EstimateExecutingView::EstimateExecutingView():
    OrcaView(std::string(sql())+"\nORDER BY category_id, estim.name")
{
    //ctor
}
void EstimateExecutingView::setup(SQLite::Statement& stm)
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
void EstimateExecutingView::search(const Search& search)
{
    if(!search){
        _sValues.clear();
        _iValues.clear(); 
        return query(sql());
    }
    auto params = sqlize(search, { 
        { "name", "estim.name" },
        { "obs", "estim.obs" },
        { "estimated", "estim.amount", FieldDescriptor::MONEY },
        { "accounted", "exc.amount", FieldDescriptor::MONEY },
        { "remaining", "(exec.amount-estim.amount)", FieldDescriptor::MONEY },
        { "due", "CAST(STRFTIME('%d', \"start\", due) AS INTEGER)", FieldDescriptor::INT },
        { "category", "category_id", FieldDescriptor::INT },
    });
    auto subParams = sqlize(search, {{"wallet", "wallet_id", FieldDescriptor::INT}});
    
    query(sql(params.query, subParams.query));
    _sValues = std::move(params.sValues);
    _sValues.insert(_sValues.end(), subParams.sValues.begin(), subParams.sValues.end());
    _iValues = std::move(params.iValues);
    _iValues.insert(_iValues.end(), subParams.iValues.begin(), subParams.iValues.end());
}

static std::string sql(const std::string &mainQuery, const std::string &execQuery){
    std::string s = _sql;
    auto replaceWithPrefix = [&s](const std::string &sub, const std::string &query, const std::string &prefix){
        auto i = s.find(sub);
        if(query.size()){
            s.replace(i, sub.size(), prefix+query);
        } else {
            s.replace(i, sub.size(), "");
        }
    };
    replaceWithPrefix("{{main}}", mainQuery, " AND ");
    replaceWithPrefix("{{sub}}", execQuery, "WHERE ");
    return s;
}

