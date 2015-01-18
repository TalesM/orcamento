#ifndef EXECUTIONDIALOG_H
#define EXECUTIONDIALOG_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(ExecutionDialog)
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/gbsizer.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(ExecutionDialog)
#include <wx/grid.h>
//*)

class ExecutionDialog: public wxDialog
{
	public:

		ExecutionDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExecutionDialog();

		//(*Declarations(ExecutionDialog)
		wxTextCtrl* txEstimateAmount;
		wxButton* btAdd;
		wxButton* btClose;
		wxGrid* gdExecutions;
		wxTextCtrl* txBudget;
		wxTextCtrl* txEstimateName;
		//*)

	protected:

		//(*Identifiers(ExecutionDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_GRID1;
		static const long ID_EXECUTION_ADD;
		//*)

	private:

		//(*Handlers(ExecutionDialog)
		void OnbtAddClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
