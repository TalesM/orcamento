#include "wx_pch.h"
#include "ExecutionDialog.h"

#include <vector>
#include "actions/DeleteExecution.h"
#include "actions/InsertExecution.h"
#include "actions/UpdateExecution.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(ExecutionDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(ExecutionDialog)
//*)

//(*IdInit(ExecutionDialog)
const long ExecutionDialog::ID_TEXTCTRL1 = wxNewId();
const long ExecutionDialog::ID_TEXTCTRL2 = wxNewId();
const long ExecutionDialog::ID_TEXTCTRL3 = wxNewId();
const long ExecutionDialog::ID_STATICTEXT1 = wxNewId();
const long ExecutionDialog::ID_STATICTEXT2 = wxNewId();
const long ExecutionDialog::ID_TEXTCTRL4 = wxNewId();
const long ExecutionDialog::ID_TEXTCTRL5 = wxNewId();
const long ExecutionDialog::ID_GRID1 = wxNewId();
const long ExecutionDialog::ID_EXECUTION_ADD = wxNewId();
const long ExecutionDialog::ID_BTDELETE = wxNewId();
//*)

namespace ExecutionColumn{
    constexpr int
        ID          = 0,
        AMOUNT      = 1,
        DATE        = 2,
        WALLET      = 3,
        DESCRIPTION = 4,
        OBS         = 5;
    constexpr int length = 6;
};

BEGIN_EVENT_TABLE(ExecutionDialog,wxDialog)
	//(*EventTable(ExecutionDialog)
	//*)
END_EVENT_TABLE()

ExecutionDialog::ExecutionDialog(wxWindow* parent,wxWindowID id, int estimateId,const wxPoint& pos,const wxSize& size):
    _estimateId(estimateId)
{
	//(*Initialize(ExecutionDialog)
	wxStaticText* StaticText2;
	wxStaticText* StaticText1;
	wxStaticText* StaticText3;
	wxStaticText* StaticText4;
	wxGridBagSizer* gbzExecution;

	Create(parent, wxID_ANY, _("Execution"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
	gbzExecution = new wxGridBagSizer(0, 0);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Budget:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText1, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txBudget = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	gbzExecution->Add(txBudget, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txEstimateName = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	gbzExecution->Add(txEstimateName, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Estimated:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText3, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txEstimateAmount = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	gbzExecution->Add(txEstimateAmount, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText5 = new wxStaticText(this, ID_STATICTEXT1, _("Accounted"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	gbzExecution->Add(StaticText5, wxGBPosition(3, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(this, ID_STATICTEXT2, _("Leftover"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	gbzExecution->Add(StaticText6, wxGBPosition(4, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txAccounted = new wxTextCtrl(this, ID_TEXTCTRL4, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
	gbzExecution->Add(txAccounted, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txLeftover = new wxTextCtrl(this, ID_TEXTCTRL5, _("Text"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL5"));
	gbzExecution->Add(txLeftover, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, wxID_ANY, _("History:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText4, wxGBPosition(5, 0), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	gdExecutions = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	gdExecutions->CreateGrid(0,6);
	gdExecutions->SetMinSize(wxSize(-1,250));
	gdExecutions->EnableEditing(true);
	gdExecutions->EnableGridLines(true);
	gdExecutions->SetColLabelValue(0, _("Id"));
	gdExecutions->SetColLabelValue(1, _("Amount"));
	gdExecutions->SetColLabelValue(2, _("Date"));
	gdExecutions->SetColLabelValue(3, _("Wallet"));
	gdExecutions->SetColLabelValue(4, _("Description"));
	gdExecutions->SetColLabelValue(5, _("Obs."));
	gdExecutions->SetDefaultCellFont( gdExecutions->GetFont() );
	gdExecutions->SetDefaultCellTextColour( gdExecutions->GetForegroundColour() );
	gbzExecution->Add(gdExecutions, wxGBPosition(6, 0), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btAdd = new wxButton(this, ID_EXECUTION_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EXECUTION_ADD"));
	btAdd->SetMinSize(wxSize(-1,-1));
	gbzExecution->Add(btAdd, wxGBPosition(7, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btDelete = new wxButton(this, ID_BTDELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BTDELETE"));
	gbzExecution->Add(btDelete, wxGBPosition(7, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	btClose = new wxButton(this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	gbzExecution->Add(btClose, wxGBPosition(8, 1), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("Item Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText2, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(gbzExecution);
	gbzExecution->Fit(this);
	gbzExecution->SetSizeHints(this);

	Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&ExecutionDialog::OngdExecutionsCellChange);
	Connect(ID_EXECUTION_ADD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExecutionDialog::OnbtAddClick);
	Connect(ID_BTDELETE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExecutionDialog::OnbtDeleteClick);
	//*)
	gbzExecution->AddGrowableCol(1);
	gbzExecution->AddGrowableRow(4);
	gdExecutions->HideCol(0);
}

ExecutionDialog::~ExecutionDialog()
{
	//(*Destroy(ExecutionDialog)
	//*)
}

void ExecutionDialog::giveDatabase(std::unique_ptr<OrcaDocument>& database)
{
    _document = std::move(database);
    RefreshModel();
}

void ExecutionDialog::RefreshModel(){
    try{
        _executionSummaryView.estimateId(_estimateId);
        bool done = false;
        _document->look(_executionSummaryView, [this, &done](const std::string &budgetName,
                                                           const std::string &estimateName,
                                                           double estimated, double accounted,
                                                           double remaining, int count)
        {
            assert(!done);
            done = true;
            txBudget->SetValue(wxString::FromUTF8(budgetName.c_str()));
            txEstimateName->SetValue(wxString::FromUTF8(estimateName.c_str()));
            txEstimateAmount->SetValue(wxString::FromDouble(estimated, 2));
            txAccounted->SetValue(wxString::FromDouble(accounted, 2));
            txLeftover->SetValue(wxString::FromDouble(remaining, 2));
            if(count > 0){
                RefreshExecutions();
            }
        });
        if(!done){
            wxMessageBox("Database possibly corrupted, do you have a backup?");
        }
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}
void ExecutionDialog::RefreshExecutions()
{
    if(gdExecutions->GetNumberRows()){
        gdExecutions->DeleteRows(0, gdExecutions->GetNumberRows());
    }
    try{
        _executionView.estimateId(_estimateId);
        int i = 0;
        _document->look(_executionView, [this, &i](int id, double amount,
                                               const std::string &date,
                                               const std::string &wallet,
                                               const std::string &description,
                                               const std::string &obs)
        {
            gdExecutions->AppendRows();
            gdExecutions->SetCellValue(i, ExecutionColumn::ID,          wxString::FromDouble(id) );
            gdExecutions->SetCellValue(i, ExecutionColumn::AMOUNT,      wxString::FromDouble(amount, 2) );
            gdExecutions->SetCellValue(i, ExecutionColumn::DATE,        wxString::FromUTF8(date.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::WALLET,      wxString::FromUTF8(wallet.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::DESCRIPTION, wxString::FromUTF8(description.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::OBS,         wxString::FromUTF8(obs.c_str()) );
            ++i;
        });
        RefreshCellAttr();
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void ExecutionDialog::RefreshCellAttr()
{
    wxGridCellAttr *attrReadOnly = new wxGridCellAttr();
    attrReadOnly->SetReadOnly();
    gdExecutions->SetColAttr(ExecutionColumn::ID, attrReadOnly);

    wxGridCellAttr *attrAmount = new wxGridCellAttr();
    attrAmount->SetRenderer(new wxGridCellFloatRenderer(-1, 2));
    attrAmount->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdExecutions->SetColAttr(ExecutionColumn::AMOUNT, attrAmount);

    wxGridCellAttr *attrDate = new wxGridCellAttr();
    attrDate->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdExecutions->SetColAttr(ExecutionColumn::DATE, attrDate);

    attrReadOnly->IncRef();
    gdExecutions->SetColAttr(ExecutionColumn::WALLET, attrReadOnly);
}


void ExecutionDialog::OnbtAddClick(wxCommandEvent& event)
{
    std::vector<int> walletIds;
    wxArrayString walletNames;
    try {
        _document->look(_walletView, [&walletIds, &walletNames](int id, const std::string &name){
            walletIds.push_back(id);
            walletNames.push_back(wxString::FromUTF8(name.c_str()));
        });
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
    int selected = wxGetSingleChoiceIndex(L"Choose the wallet to pay/receive money", L"Choose Wallet", walletNames);
    if(selected < 0){
        return;
    }
    try{
        _document->exec<action::InsertExecution>(_estimateId, walletIds[selected]);
        RefreshExecutions();
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void ExecutionDialog::OngdExecutionsCellChange(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    wxString newValue = gdExecutions->GetCellValue(row, col);
    if(event.GetString() == gdExecutions->GetCellValue(row, col)){//The default editor duplicate events, so this avoids the first one.
        return;
    }
    long id;
    if(!gdExecutions->GetCellValue(row, ExecutionColumn::ID).ToCLong(&id)){
        wxMessageBox(L"Corrupted Line: #"+gdExecutions->GetRowLabelValue(row));
        return;
    }
    auto updateField = [this, id=int(id)](std::string field, const auto &value){
        try{
            std::string query = "UPDATE execution SET \""+field+"\" = ?2 WHERE execution_id = ?1";
            SQLite::Statement stm(_document->_model, query);
            stm.bind(1, id);
            stm.bind(2, value);
            if(!stm.exec()){
                wxMessageBox("Unknown Error");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    };
    int executionId = int(id);
    switch(col){
    case ExecutionColumn::AMOUNT:
        _document->exec<action::UpdateExecutionAmount>(executionId, atof(newValue));
        RefreshModel();
        break;
    case ExecutionColumn::DATE:
        try{
            std::string query = "UPDATE execution SET \"date\" = date(?2) WHERE execution_id = ?1";
            SQLite::Statement stm(_document->_model, query);
            stm.bind(1, int(id));
            stm.bind(2, newValue);
            if(!stm.exec()){
                wxMessageBox("Unknown Error");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        break;
    case ExecutionColumn::DESCRIPTION:
        updateField("description", newValue.ToUTF8());
        break;
    case ExecutionColumn::OBS:
        updateField("obs", newValue.ToUTF8());
        break;
    default:
        break;
    }
}

void ExecutionDialog::OnbtDeleteClick(wxCommandEvent& event)
{
    wxArrayInt arrSelected = gdExecutions->GetSelectedRows();
    if(arrSelected.size() == 0){
        wxMessageBox("You need to select a row to delete");
        return;
    }
    if(wxMessageBox(L"Are you sure you want do delete these executions?", "Confirm Delete", wxOK | wxCENTRE | wxCANCEL | wxICON_QUESTION, this) != wxOK){
        return;
    }
    try{
        for(int row: arrSelected){
            int id = atoi(gdExecutions->GetCellValue(row, ExecutionColumn::ID));
            _document->exec<action::DeleteExecution>(id);
        }
        RefreshExecutions();
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}
