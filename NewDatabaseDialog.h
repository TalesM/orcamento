#ifndef NEWDATABASEDIALOG_H
#define NEWDATABASEDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(NewDatabaseDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/choice.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(NewDatabaseDialog)
#include <wx/datectrl.h>
#include <wx/filepicker.h>
#include <wx/spinctrl.h>
#include <wx/dateevt.h>
//*)

class NewDatabaseDialog: public wxDialog
{
	public:

		NewDatabaseDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~NewDatabaseDialog();

		//(*Declarations(NewDatabaseDialog)
		wxDatePickerCtrl* DatePickerCtrl1;
		wxSpinCtrl* intervalSpin;
		wxTextCtrl* nameTextCtrl;
		wxChoice* intervalChoice;
		wxFilePickerCtrl* filePicker;
		//*)

	protected:

		//(*Identifiers(NewDatabaseDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_FILEPICKERCTRL1;
		static const long ID_DATEPICKERCTRL1;
		static const long ID_SPINCTRL1;
		static const long ID_CHOICE1;
		//*)

	private:

		//(*Handlers(NewDatabaseDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
