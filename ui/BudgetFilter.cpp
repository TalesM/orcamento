#include "BudgetFilter.h"
#include <string>
#include "model/OrcaDocument.h"
#include "model/views/CategoryView.h"
#include "model/views/WalletView.h"

using namespace std;

BudgetFilter::BudgetFilter(wxWindow* parent)
    : BudgetFilterBase(parent)
{
    SetLayoutAdaptationMode(wxDIALOG_ADAPTATION_MODE_ENABLED);
}

BudgetFilter::~BudgetFilter()
{
}


void BudgetFilter::refreshFields(OrcaDocument &doc)
{
    lsckCategories->Clear();
    CategoryView categoryView;
    doc.look(categoryView, [this](int id, const std::string name){
        lsckCategories->Append(wxString::FromUTF8(name.c_str()), reinterpret_cast<void*>(id));
    });
    
    lsckWallets->Clear();
    WalletView walletView;
    doc.look(walletView, [this](int id, const std::string name){
        lsckWallets->Append(wxString::FromUTF8(name.c_str()), reinterpret_cast<void*>(id));
    });
}


void BudgetFilter::OnBtrefreshButtonClicked(wxCommandEvent& event)
{
    _search = search("");
    auto bogusSearch = _search;
    //Makes sintax ahead easier
    auto _and = [this](const Search& s) { _search = _search && s; };
    //Makes text comparation easier
    auto textParse = [&_and](const std::string &field, wxTextCtrl *value, wxChoice *comparation, bool invert = false){
        auto s = search(field);
        auto sValue = std::string(value->GetValue().ToUTF8());
        if(sValue.size() == 0){
            return;
        }
        switch(comparation->GetSelection()) {
        case 0:
            _and(s->contains(sValue));
            break;
        case 1:
            _and(s->prefix(sValue));
            break;
        case 2:
            _and(s->suffix(sValue));
            break;
        case 3:
            _and(s->equal(sValue));
            break;
        default:
            throw std::runtime_error("Unknown Value");
        }
    };
    auto moneyParse = [&_and](const std::string &field, wxTextCtrl *minValue, wxTextCtrl *maxValue, bool invert = false){
        auto min = string(minValue->GetValue());
        auto max = string(maxValue->GetValue());
        auto s = search("estimated");
        if(min.size() > 0){
            _and(s >= std::string(min));
        }
        if(max.size() > 0){
            _and(s <= std::string(max));
        }
    };
    auto groupParse = [&_and](const std::string &field, wxCheckListBox *values, bool invert = false){
        wxArrayInt ls;
        if(not values->GetCheckedItems(ls)){
            return;
        }
        Search s = search(field);
        auto _or = [&s](const Search& t){s = s || t;};
        for(auto &&i: ls){
            _or(search(field) == reinterpret_cast<int>(values->GetClientData(i)));
        }
        _and(s);
    };
    //Making the search
    textParse("name", txName, chName);
    textParse("obs", txObservation, chObservation);
    moneyParse("estimated", txEstimatedFrom, txEstimatedTo);
    moneyParse("accounted", txAccountedFrom, txAccountedTo);
    moneyParse("remaining", txRemainingFrom, txRemainingTo);
    if(spDateFrom->GetValue() > 1){
        _and(search("due") >= spDateFrom->GetValue());
    }
    if(spDateTo->GetValue() < 31){
        _and(search("due") <= spDateTo->GetValue());
    }
    groupParse("category", lsckCategories);
    groupParse("wallet", lsckWallets);
    
    if(_search == bogusSearch) {
        _search = nullptr;
    }
    for(auto&& listener : _searchListener) {
        listener(_search);
    }
}
void BudgetFilter::OnBtcloseButtonClicked(wxCommandEvent& event)
{
    OnBtrefreshButtonClicked(event);
    Close();
}
