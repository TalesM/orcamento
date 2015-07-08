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
    ORDER BY {{sort}} category_id, estim.name
)=";


static std::string sql(const std::string &mainQuery="", const std::string &execQuery="", const std::string &sort="");

EstimateExecutingView::EstimateExecutingView():
    OrcaView(std::string(sql()))
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
void EstimateExecutingView::search(const Search& search, int order, bool asc)
{
    std::string sort = "";
    const char *orders[] = {
        "category_id",
        "lower(estim.name)",
        "CAST(STRFTIME('%d', \"start\", due) AS INTEGER)",
        "estim.amount",
        "exc.amount",
        "(exc.amount-estim.amount)",
        "category_id",
        "estim.obj",
    };
    sort += orders[order];
    if(not asc){
        sort += " DESC";
    }
    if(!search){
        _sValues.clear();
        _iValues.clear(); 
        return query(sql("", "", sort));
    }
    auto params = sqlize(search, { 
        { "name",       "estim.name" },
        { "obs",        "estim.obs" },
        { "estimated",  "estim.amount", FieldDescriptor::MONEY },
        { "accounted",  "exc.amount", FieldDescriptor::MONEY },
        { "remaining",  "(exc.amount-estim.amount)", FieldDescriptor::MONEY },
        { "due",        "CAST(STRFTIME('%d', \"start\", due) AS INTEGER)", FieldDescriptor::INT },
        { "category",   "category_id", FieldDescriptor::INT },
    });
    auto subParams = sqlize(search, {{"wallet", "wallet_id", FieldDescriptor::INT}});
    
    query(sql(params.query, subParams.query));
    _sValues = std::move(params.sValues);
    _sValues.insert(_sValues.end(), subParams.sValues.begin(), subParams.sValues.end());
    _iValues = std::move(params.iValues);
    _iValues.insert(_iValues.end(), subParams.iValues.begin(), subParams.iValues.end());
}

static std::string sql(const std::string &mainQuery, const std::string &execQuery, const std::string &sort){
    std::string s = _sql;
    auto replaceWithPrefix = [&s](const std::string &sub, const std::string &query, const std::string &prefix, bool suffix=false){
        auto i = s.find(sub);
        if(query.size()){
            if(suffix){
                s.replace(i, sub.size(), query+prefix);
            }else {
                s.replace(i, sub.size(), prefix+query);
            }
        } else {
            s.replace(i, sub.size(), "");
        }
    };
    replaceWithPrefix("{{main}}", mainQuery, " AND ");
    replaceWithPrefix("{{sub}}", execQuery, "WHERE ");
    replaceWithPrefix("{{sort}}", sort, ", ", true);
    return s;
}

