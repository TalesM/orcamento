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
const long CreateDatabaseDialog::ID_TEXTCTRL1 = wxNewId();
const long CreateDatabaseDialog::ID_FILEPICKERCTRL1 = wxNewId();
const long CreateDatabaseDialog::ID_DATEPICKERCTRL1 = wxNewId();
const long CreateDatabaseDialog::ID_SPINCTRL1 = wxNewId();
const long CreateDatabaseDialog::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CreateDatabaseDialog,wxDialog)
	//(*EventTable(CreateDatabaseDialog)
	//*)
END_EVENT_TABLE()

CreateDatabaseDialog::CreateDatabaseDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(CreateDatabaseDialog)
	wxStaticText* StaticText2;
	wxStaticText* StaticText1;
	wxBoxSizer* BoxSizer2;
	wxStaticText* StaticText3;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticText* StaticText4;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("Setup Database"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	StaticText1 = new wxStaticText(this, wxID_ANY, _("Name"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	nameTextCtrl = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer1->Add(nameTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
	StaticText2 = new wxStaticText(this, wxID_ANY, _("Location"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	filePicker = new wxFilePickerCtrl(this, ID_FILEPICKERCTRL1, wxEmptyString, wxEmptyString, _T("*.orca"), wxDefaultPosition, wxDefaultSize, wxFLP_OVERWRITE_PROMPT|wxFLP_SAVE|wxFLP_USE_TEXTCTRL, wxDefaultValidator, _T("ID_FILEPICKERCTRL1"));
	FlexGridSizer1->Add(filePicker, 1, wxALL|wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
	StaticText3 = new wxStaticText(this, wxID_ANY, _("Start"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText3, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	DatePickerCtrl1 = new wxDatePickerCtrl(this, ID_DATEPICKERCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_DATEPICKERCTRL1"));
	FlexGridSizer1->Add(DatePickerCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(this, wxID_ANY, _("Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	intervalSpin = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 15, 1, _T("ID_SPINCTRL1"));
	intervalSpin->SetValue(_T("1"));
	BoxSizer2->Add(intervalSpin, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	intervalChoice = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	intervalChoice->Append(_("days"));
	intervalChoice->Append(_("weeks"));
	intervalChoice->SetSelection( intervalChoice->Append(_("months")) );
	BoxSizer2->Add(intervalChoice, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer1->Add(FlexGridSizer1, 4, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
