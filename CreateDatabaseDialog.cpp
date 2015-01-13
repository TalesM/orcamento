#include "wx_pch.h"
#include "CreateDatabaseDialog.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(CreateDatabaseDialog)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(CreateDatabaseDialog)
#include <wx/button.h>
//*)

//(*IdInit(CreateDatabaseDialog)
const long CreateDatabaseDialog::ID_FILEPICKERCTRL1 = wxNewId();
const long CreateDatabaseDialog::ID_DATEPICKERCTRL = wxNewId();
//*)

BEGIN_EVENT_TABLE(CreateDatabaseDialog,wxDialog)
	//(*EventTable(CreateDatabaseDialog)
	//*)
END_EVENT_TABLE()

CreateDatabaseDialog::CreateDatabaseDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(CreateDatabaseDialog)
	wxStaticText* StaticText2;
	wxStaticText* StaticText3;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Setup Database"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("Location"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	fpLocation = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, _T("*.orca"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	FlexGridSizer1->Add(fpLocation, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	dpStart = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL"));
	FlexGridSizer1->Add(dpStart, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(FlexGridSizer1, 2, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
}

CreateDatabaseDialog::~CreateDatabaseDialog()
{
	//(*Destroy(CreateDatabaseDialog)
	//*)
}


void CreateDatabaseDialog::OnClose(wxCloseEvent& event)
{
}
