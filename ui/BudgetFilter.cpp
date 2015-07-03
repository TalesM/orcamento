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
    if(txName->GetValue().size()){
        _search = search("name")->contains(std::string(txName->GetValue().ToUTF8()));
    } else {
        _search = nullptr;
    }
    for(auto &&listener: _searchListener){
        listener(_search);
    }
}
