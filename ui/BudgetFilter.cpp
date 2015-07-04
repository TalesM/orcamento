#include "BudgetFilter.h"
#include <string>

using namespace std;

BudgetFilter::BudgetFilter(wxWindow* parent)
    : BudgetFilterBase(parent)
{
}

BudgetFilter::~BudgetFilter()
{
}

void BudgetFilter::OnBtrefreshButtonClicked(wxCommandEvent& event)
{
    _search = search("");
    auto bogusSearch = _search;
    auto and_ = [this](const Search &s){
        _search = _search && s;
    };
    
    if(txName->GetValue().size()){
        auto s = search("name")->contains(std::string(txName->GetValue().ToUTF8()));
        
        and_(s);
    }
    if(_search==bogusSearch){
        _search = nullptr;
    }
    for(auto &&listener: _searchListener){
        listener(_search);
    }
}
