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
    _search = search("estimate.name")->contains(std::string(txName->GetValue().ToUTF8()));
    for(auto &&listener: _searchListener){
        listener(_search);
    }
}
