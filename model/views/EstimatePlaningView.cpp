#include "EstimatePlaningView.h"

static auto sql = R"=(
SELECT 
    estim.estimate_id,
    estim.name AS name,
    STRFTIME("%d", bud.start, estim.due) AS due,
    estim.amount/100.0 AS estimated,
    cat.name AS category, 
    estim.obs AS obs
FROM budget bud
    JOIN estimate estim USING(budget_id)
    JOIN category cat USING(category_id)
  WHERE budget_id = :budget
)=";

EstimatePlaningView::EstimatePlaningView():
    OrcaView(std::string(sql)+"\nORDER BY category_id, estim.name")
{
    //ctor
}

void EstimatePlaningView::setup(SQLite::Statement& stm)
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
void EstimatePlaningView::search(const Search& search)
{
    if(!search){
        _sValues.clear();
        _iValues.clear();
        return query(sql);
    }
    auto params = sqlize(search, { 
        { "name", "estim.name" },
        { "obs", "estim.obs" },
        { "estimated", "estim.amount", FieldDescriptor::MONEY },
        { "due", "CAST(STRFTIME('%d', \"start\", due) AS INTEGER)", FieldDescriptor::INT },
        { "category", "category_id", FieldDescriptor::INT },
    });
    if(!params.query.size()){
        return query(sql + std::string("\nORDER BY category_id, estim.name"));
    }
    
    _sValues = std::move(params.sValues);
    _iValues = std::move(params.iValues);
    query(std::string(sql) + " AND " + params.query + "\nORDER BY category_id, estim.name");
}

