#ifndef BUDGETFILTER_H
#define BUDGETFILTER_H

#include "wxcrafter.h"
#include "model/SearchOption.h"
#include <functional>
#include <vector>

class BudgetFilter : public BudgetFilterBase
{
public:
    typedef std::function<void(Search)> SearchListener; 
    BudgetFilter(wxWindow* parent);
    virtual ~BudgetFilter();
    
    void addSearchListerner(const SearchListener &searchListener){
        _searchListener.push_back(searchListener);
    }
    
private:
    Search _search;
    std::vector<SearchListener> _searchListener;
protected:
    virtual void OnBtrefreshButtonClicked(wxCommandEvent& event);
};
#endif // BUDGETFILTER_H
