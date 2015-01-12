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
	wxBoxSizer* BoxSizer2;
	wxStaticText* StaticText3;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	wxStaticText* StaticText4;
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
	StaticText4 = new wxStaticText(this, wxID_ANY, _("Interval"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	FlexGridSizer1->Add(StaticText4, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	spInterval = new wxSpinCtrl(this, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 15, 1, _T("ID_SPINCTRL1"));
	spInterval->SetValue(_T("1"));
	BoxSizer2->Add(spInterval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	chInterval = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	chInterval->Append(_("days"));
	chInterval->Append(_("weeks"));
	chInterval->SetSelection( chInterval->Append(_("months")) );
	BoxSizer2->Add(chInterval, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
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
