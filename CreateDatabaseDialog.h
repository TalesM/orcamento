#ifndef CREATEDATABASEDIALOG_H
#define CREATEDATABASEDIALOG_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#ifndef WX_PRECOMP
	//(*HeadersPCH(CreateDatabaseDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
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

		wxString getLocation(){
		    return fpLocation->GetPath();
		}

		wxDateTime getStart(){
		    return dpStart->GetValue();
//		    return date.Format("%F");
		}

		wxString getDuration(){
		    wxString result;
		    result << spInterval->GetValue() << L" " << chInterval->GetString(chInterval->GetSelection());
		    return result;
		}

	protected:

		//(*Identifiers(CreateDatabaseDialog)
		static const long ID_FILEPICKERCTRL1;
		static const long ID_DATEPICKERCTRL;
		static const long ID_SPINCTRL1;
		static const long ID_CHOICE1;
		//*)

	private:
		//(*Handlers(CreateDatabaseDialog)
		void OnClose(wxCloseEvent& event);
		//*)

		//(*Declarations(CreateDatabaseDialog)
		wxDatePickerCtrl* dpStart;
		wxFilePickerCtrl* fpLocation;
		wxSpinCtrl* spInterval;
		wxChoice* chInterval;
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
