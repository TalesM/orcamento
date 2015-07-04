#ifndef _ORCA_ESTIMATEEXECUTINGVIEW_H
#define _ORCA_ESTIMATEEXECUTINGVIEW_H

#include "../OrcaView.h"
#include "../Search.h"

class EstimateExecutingView : public OrcaView<
    int,            //estimate_id
    std::string,    //estimate.name
    std::string,    //Due date
    double,         //estimated/100
    double,         //accounted/100
    double,         //remaining/100
    std::string,    //category.name
    std::string     //estimate.obs
    >
{
public:
    EstimateExecutingView();
    virtual ~EstimateExecutingView() {}

    int budgetId() const {
        return _budgetId;
    }

    void budgetId(int value){
        _budgetId = value;
    }
    
    void search(const Search &s);
private:
    int _budgetId;
    SearchQuery _params;

    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_ESTIMATEEXECUTINGVIEW_H
