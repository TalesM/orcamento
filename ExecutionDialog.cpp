#include "wx_pch.h"
#include "ExecutionDialog.h"

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
const long ExecutionDialog::ID_GRID1 = wxNewId();
const long ExecutionDialog::ID_EXECUTION_ADD = wxNewId();
//*)

BEGIN_EVENT_TABLE(ExecutionDialog,wxDialog)
	//(*EventTable(ExecutionDialog)
	//*)
END_EVENT_TABLE()

ExecutionDialog::ExecutionDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
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
	txBudget = new wxTextCtrl(this, ID_TEXTCTRL1, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	gbzExecution->Add(txBudget, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txEstimateName = new wxTextCtrl(this, ID_TEXTCTRL2, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	gbzExecution->Add(txEstimateName, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Estimated:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText3, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	txEstimateAmount = new wxTextCtrl(this, ID_TEXTCTRL3, _("Text"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
	gbzExecution->Add(txEstimateAmount, wxGBPosition(2, 1), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, wxID_ANY, _("Accounted:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText4, wxGBPosition(3, 0), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	gdExecutions = new wxGrid(this, ID_GRID1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_GRID1"));
	gdExecutions->CreateGrid(1,6);
	gdExecutions->SetMinSize(wxSize(-1,250));
	gdExecutions->EnableEditing(true);
	gdExecutions->EnableGridLines(true);
	gdExecutions->SetColLabelValue(0, _("Id"));
	gdExecutions->SetColLabelValue(1, _("Amount"));
	gdExecutions->SetColLabelValue(2, _("Date"));
	gdExecutions->SetColLabelValue(3, _("Wallet"));
	gdExecutions->SetColLabelValue(4, _("Description"));
	gdExecutions->SetColLabelValue(5, _("Obs."));
	gdExecutions->SetRowLabelValue(0, _("Total"));
	gdExecutions->SetCellValue(0, 0, _("0"));
	gdExecutions->SetCellValue(0, 1, _("0.0"));
	gdExecutions->SetDefaultCellFont( gdExecutions->GetFont() );
	gdExecutions->SetDefaultCellTextColour( gdExecutions->GetForegroundColour() );
	gbzExecution->Add(gdExecutions, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btAdd = new wxButton(this, ID_EXECUTION_ADD, _("Add"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_EXECUTION_ADD"));
	btAdd->SetMinSize(wxSize(-1,-1));
	gbzExecution->Add(btAdd, wxGBPosition(5, 0), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	btClose = new wxButton(this, wxID_CANCEL, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
	gbzExecution->Add(btClose, wxGBPosition(6, 1), wxDefaultSpan, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("Item Name:"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	gbzExecution->Add(StaticText2, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(gbzExecution);
	gbzExecution->Fit(this);
	gbzExecution->SetSizeHints(this);

	Connect(ID_EXECUTION_ADD,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExecutionDialog::OnbtAddClick);
	//*)
	gbzExecution->AddGrowableCol(1);
	gbzExecution->AddGrowableRow(4);
}

ExecutionDialog::~ExecutionDialog()
{
	//(*Destroy(ExecutionDialog)
	//*)
}


void ExecutionDialog::OnbtAddClick(wxCommandEvent& event)
{
    gdExecutions->InsertRows();
}
