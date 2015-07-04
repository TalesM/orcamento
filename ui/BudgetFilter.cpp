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
    auto and_ = [this](const Search& s) { _search = _search && s; };
    auto textParse = [&and_](const std::string &field, wxTextCtrl *value, wxChoice *comparation, bool invert = false){
        auto s = search(field);
        auto sValue = std::string(value->GetValue().ToUTF8());
        switch(comparation->GetSelection()) {
        case 0:
            and_(s->contains(sValue));
            break;
        case 1:
            and_(s->prefix(sValue));
            break;
        case 2:
            and_(s->suffix(sValue));
            break;
        case 3:
            and_(s->equal(sValue));
            break;
        default:
            throw std::runtime_error("Unknown Value");
        }
    };

    //Making the search
    if(txName->GetValue().size()) {
        textParse("name", txName, chName);
    }
    if(txObservation->GetValue().size()) {
        textParse("obs", txObservation, chObservation);
    }
    
    
    if(_search == bogusSearch) {
        _search = nullptr;
    }
    for(auto&& listener : _searchListener) {
        listener(_search);
    }
}
