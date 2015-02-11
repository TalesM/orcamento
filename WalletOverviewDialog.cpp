#include "wx_pch.h"
#include <algorithm>
#include "WalletOverviewDialog.h"
#include "actions/InsertWallet.h"
#include "actions/UpdateWallet.h"

#ifndef WX_PRECOMP
//(*InternalHeadersPCH(WalletOverviewDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#endif
//(*InternalHeaders(WalletOverviewDialog)
//*)

//(*IdInit(WalletOverviewDialog)
const long WalletOverviewDialog::ID_SIMPLEHTMLLISTBOX1 = wxNewId();
const long WalletOverviewDialog::ID_TX_NAME = wxNewId();
const long WalletOverviewDialog::ID_TX_OBS = wxNewId();
//*)

BEGIN_EVENT_TABLE(WalletOverviewDialog,wxDialog)
    //(*EventTable(WalletOverviewDialog)
    //*)
END_EVENT_TABLE()

WalletOverviewDialog::WalletOverviewDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(WalletOverviewDialog)
    wxStaticText* StaticText2;
    wxStaticText* StaticText1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("Wallet Overview"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    lsWallets = new wxSimpleHtmlListBox(this, ID_SIMPLEHTMLLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, wxHLB_DEFAULT_STYLE, wxDefaultValidator, _T("ID_SIMPLEHTMLLISTBOX1"));
    lsWallets->Append(_("T1"));
    lsWallets->Append(_("T2"));
    lsWallets->Append(_("T43"));
    BoxSizer1->Add(lsWallets, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1 = new wxFlexGridSizer(3, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(1);
    StaticText1 = new wxStaticText(this, wxID_ANY, _("Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txName = new wxTextCtrl(this, ID_TX_NAME, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TX_NAME"));
    FlexGridSizer1->Add(txName, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, wxID_ANY, _("Obs"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txObs = new wxTextCtrl(this, ID_TX_OBS, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TX_OBS"));
    FlexGridSizer1->Add(txObs, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(FlexGridSizer1, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    btEdit = new wxButton(this, wxID_APPLY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_APPLY"));
    btEdit->Disable();
    BoxSizer2->Add(btEdit, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btAdd = new wxButton(this, wxID_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_ADD"));
    btAdd->Disable();
    BoxSizer2->Add(btAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btRemove = new wxButton(this, wxID_REMOVE, _("Remove"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_REMOVE"));
    btRemove->Disable();
    BoxSizer2->Add(btRemove, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_SIMPLEHTMLLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&WalletOverviewDialog::OnlsWalletsSelect);
    Connect(ID_TX_NAME,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&WalletOverviewDialog::OntxNameText);
    Connect(ID_TX_OBS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&WalletOverviewDialog::OntxObsText);
    Connect(wxID_APPLY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WalletOverviewDialog::OnbtEditClick);
    Connect(wxID_ADD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WalletOverviewDialog::OnbtAddClick);
    Connect(wxID_REMOVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&WalletOverviewDialog::OnbtRemoveClick);
    //*)
}

WalletOverviewDialog::~WalletOverviewDialog()
{
    //(*Destroy(WalletOverviewDialog)
    //*)
}

void WalletOverviewDialog::giveDatabase(std::unique_ptr<OrcaDocument>& database)
{
    _document = std::move(database);
    lsWallets->Clear();
    try {
        _document->look(_walletView, [this](int, const std::string &name) {
            lsWallets->Append(wxString::FromUTF8(name.c_str()));
        });
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}


void WalletOverviewDialog::OnlsWalletsSelect(wxCommandEvent& event)
{
    try {
        bool retrieved = false;
        _walletDetailView.walletId(lsWallets->GetSelection()+1);
        _document->look(_walletDetailView, [this, &retrieved](const std::string &name, const std::string &obs, bool hasExecution) {
            txName->ChangeValue(wxString::FromUTF8(name.c_str()));
            txObs->ChangeValue(wxString::FromUTF8(obs.c_str()));
            btRemove->Enable(not hasExecution);//Always false, but I intend to fix.
            retrieved = true;
        });
        if(!retrieved) {
            wxMessageBox("Error while retrieving wallet info.");
        }

    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}

void WalletOverviewDialog::OntxNameText(wxCommandEvent& event)
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

void WalletOverviewDialog::OntxObsText(wxCommandEvent& event)
{
    int id = lsWallets->GetSelection() + 1;
    if(id > 0) {
        btEdit->Enable();
    }
}

void WalletOverviewDialog::OnbtEditClick(wxCommandEvent& event)
{
    try {
        // TODO (Tales#1#): Don't use wallet position to deduce id. It can break once we support delete.
        int walletId = lsWallets->GetSelection()+1;
        std::string name(txName->GetValue().ToUTF8()), obs(txObs->GetValue().ToUTF8());
        _document->exec<action::UpdateWallet>(walletId, name, obs);
        lsWallets->SetString(lsWallets->GetSelection(), txName->GetValue());
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}

void WalletOverviewDialog::OnbtAddClick(wxCommandEvent& event)
{
    try {
        std::string name(txName->GetValue().ToUTF8()), obs(txObs->GetValue().ToUTF8());
        _document->exec<action::InsertWallet>(name, obs);
        lsWallets->Append(txName->GetValue());
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}

void WalletOverviewDialog::OnbtRemoveClick(wxCommandEvent& event)
{
    wxMessageBox("Not implemented yet.");
}
