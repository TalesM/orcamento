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
    
    void sort(int order, bool asc = true){
        assert(order >= 0 && order < 6);
        _order = order;
        _asc = asc;
    }
private:
    int _budgetId;
    int _order = 4;
    bool _asc = true;
    std::vector<std::string> _sValues;
    std::vector<int> _iValues;


    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_ESTIMATEPLANINGVIEW_H
