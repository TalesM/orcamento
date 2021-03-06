#ifndef _ORCA_ESTIMATEPLANINGVIEW_H
#define _ORCA_ESTIMATEPLANINGVIEW_H

#include "../Search.h"
#include "../OrcaView.h"

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
    void search(const Search &search, int order=4, bool asc = true);
private:
    int _budgetId;
    std::vector<std::string> _sValues;
    std::vector<int> _iValues;


    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_ESTIMATEPLANINGVIEW_H
