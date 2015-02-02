#ifndef EXECUTIONDIALOG_H
#define EXECUTIONDIALOG_H

#include <OrcaDocument.h>
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
		wxButton* btDelete;
		//*)

		void giveDatabase(std::unique_ptr<OrcaDocument> &document);

        std::unique_ptr<OrcaDocument> takeDatabase(){
            return std::move(_document);
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
		static const long ID_BTDELETE;
		//*)

	private:
	    int _estimateId;
        std::unique_ptr<OrcaDocument> _document;

        void RefreshModel();
        void RefreshExecutions();
        void RefreshCellAttr();

		//(*Handlers(ExecutionDialog)
		void OnbtAddClick(wxCommandEvent& event);
		void OngdExecutionsCellChange(wxGridEvent& event);
		void OnbtDeleteClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
