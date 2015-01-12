#ifndef CREATEDATABASEDIALOG_H
#define CREATEDATABASEDIALOG_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#ifndef WX_PRECOMP
	//(*HeadersPCH(CreateDatabaseDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(CreateDatabaseDialog)
#include <wx/datectrl.h>
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/dateevt.h>
//*)

class CreateDatabaseDialog: public wxDialog
{
	public:

		CreateDatabaseDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~CreateDatabaseDialog();

		//(*Declarations(CreateDatabaseDialog)
		wxDatePickerCtrl* DatePickerCtrl1;
		wxSpinCtrl* intervalSpin;
		wxTextCtrl* nameTextCtrl;
		wxChoice* intervalChoice;
		wxFilePickerCtrl* filePicker;
		//*)

		wxString getLocation(){
		    return filePicker->GetPath();
		}

	protected:

		//(*Identifiers(CreateDatabaseDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_DATEPICKERCTRL1;
		static const long ID_SPINCTRL1;
		static const long ID_CHOICE1;
		//*)

	private:
		//(*Handlers(CreateDatabaseDialog)
		void OnClose(wxCloseEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
