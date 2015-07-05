#ifndef _ORCA_ESTIMATEPLANINGVIEW_H
#define _ORCA_ESTIMATEPLANINGVIEW_H

#include "../OrcaView.h"
#include "../Search.h"

class EstimatePlaningView : public OrcaView<
    int,            //estimate_id
    std::string,    //estimate.name
    std::string,    //Due date
    double,         //estimated/100
    std::string,    //category.name
    std::string     //estimate.obs
    >
{
public:
    EstimatePlaningView();
    virtual ~EstimatePlaningView(){}

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

#endif // _ORCA_ESTIMATEPLANINGVIEW_H