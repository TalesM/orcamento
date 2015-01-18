#ifndef EXECUTIONDIALOG_H
#define EXECUTIONDIALOG_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

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

		ExecutionDialog(wxWindow* parent,wxWindowID id=wxID_ANY, int estimateId =0, const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ExecutionDialog();

		//(*Declarations(ExecutionDialog)
		wxTextCtrl* txEstimateAmount;
		wxStaticText* StaticText6;
		wxButton* btAdd;
		wxButton* btClose;
		wxTextCtrl* txAccounted;
		wxTextCtrl* txLeftover;
		wxGrid* gdExecutions;
		wxStaticText* StaticText5;
		wxTextCtrl* txBudget;
		wxTextCtrl* txEstimateName;
		//*)

		void giveDatabase(std::unique_ptr<SQLite::Database> &database);

        std::unique_ptr<SQLite::Database> takeDatabase(){
            return std::move(_database);
        }

	protected:

		//(*Identifiers(ExecutionDialog)
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_TEXTCTRL3;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL4;
		static const long ID_TEXTCTRL5;
		static const long ID_GRID1;
		static const long ID_EXECUTION_ADD;
		//*)

	private:
	    int _estimateId;
        std::unique_ptr<SQLite::Database> _database;

        void RefreshModel();
        void RefreshExecutions();
        void RefreshCellAttr();

		//(*Handlers(ExecutionDialog)
		void OnbtAddClick(wxCommandEvent& event);
		void OngdExecutionsCellChange(wxGridEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
