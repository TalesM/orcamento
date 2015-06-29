#include "WalletOverviewDialog.h"
#include <algorithm>
#include "WalletOverviewDialog.h"
#include "model/actions/InsertWallet.h"
#include "model/actions/UpdateWallet.h"

WalletOverviewDialog::WalletOverviewDialog(wxWindow* parent)
    : WalletOverviewDialogBase(parent)
{
}

WalletOverviewDialog::~WalletOverviewDialog()
{
}

void WalletOverviewDialog::giveDatabase(std::unique_ptr<OrcaDocument>& database)
{
    _document = std::move(database);
    lsWallets->Clear();
    try {
        _document->look(_walletView, [this](int id, const std::string& name) { 
            lsWallets->Append(wxString::FromUTF8(name.c_str()), reinterpret_cast<void*>(id)); 
        });
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}
void WalletOverviewDialog::OnLswalletsListbox(wxCommandEvent& event)
{
    try {
        bool retrieved = false;
        _walletDetailView.walletId(reinterpret_cast<int>(lsWallets->GetClientData(lsWallets->GetSelection())));
        _document->look(_walletDetailView,
                        [this, &retrieved](const std::string& name, const std::string& obs, bool hasExecution) {
            txName->ChangeValue(wxString::FromUTF8(name.c_str()));
            txObs->ChangeValue(wxString::FromUTF8(obs.c_str()));
            btRemove->Enable(not hasExecution); // Always false, but I intend to fix.
            retrieved = true;
        });
        if(!retrieved) {
            wxMessageBox("Error while retrieving wallet info.");
        }

    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}
void WalletOverviewDialog::OnBtaddButtonClicked(wxCommandEvent& event)
{
    try {
        std::string name(txName->GetValue().ToUTF8()), obs(txObs->GetValue().ToUTF8());
        int id = _document->exec<action::InsertWallet>(name, obs);
        lsWallets->Append(txName->GetValue(), reinterpret_cast<void*>(id));
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}
void WalletOverviewDialog::OnBteditButtonClicked(wxCommandEvent& event)
{
    try {
        // TODO (Tales#1#): Don't use wallet position to deduce id. It can break once we support delete.
        int walletId = lsWallets->GetSelection() + 1;
        std::string name(txName->GetValue().ToUTF8()), obs(txObs->GetValue().ToUTF8());
        _document->exec<action::UpdateWallet>(walletId, name, obs);
        lsWallets->SetString(lsWallets->GetSelection(), txName->GetValue());
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}
void WalletOverviewDialog::OnBtremoveButtonClicked(wxCommandEvent& event)
{
    wxMessageBox("Not implemented yet.");
}
void WalletOverviewDialog::OnTxnameTextUpdated(wxCommandEvent& event)
{
    int id = lsWallets->GetSelection() + 1;
    if(id > 0) {
        btEdit->Enable();
    }
    wxArrayString strs = lsWallets->GetStrings();
    btAdd->Enable(std::none_of(strs.begin(), strs.end(), [current=txName->GetValue()](auto &str) {
        return str==current;
    }));
}
void WalletOverviewDialog::OnTxobsTextUpdated(wxCommandEvent& event)
{
    int id = lsWallets->GetSelection() + 1;
    if(id > 0) {
        btEdit->Enable();
    }
}
