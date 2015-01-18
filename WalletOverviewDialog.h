#ifndef WALLETOVERVIEW_H
#define WALLETOVERVIEW_H

#include "wx_pch.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>

#ifndef WX_PRECOMP
	//(*HeadersPCH(WalletOverviewDialog)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/htmllbox.h>
	#include <wx/button.h>
	#include <wx/dialog.h>
	//*)
#endif
//(*Headers(WalletOverviewDialog)
//*)

class WalletOverviewDialog: public wxDialog
{
	public:

		WalletOverviewDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~WalletOverviewDialog();

		//(*Declarations(WalletOverviewDialog)
		wxTextCtrl* txName;
		wxButton* Button1;
		wxButton* btAdd;
		wxButton* btRemove;
		wxTextCtrl* txObs;
		wxSimpleHtmlListBox* lsWallets;
		wxButton* btEdit;
		//*)

        void giveDatabase(std::unique_ptr<SQLite::Database> &database);

        std::unique_ptr<SQLite::Database> takeDatabase(){
            return std::move(_database);
        }

	protected:

		//(*Identifiers(WalletOverviewDialog)
		static const long ID_SIMPLEHTMLLISTBOX1;
		static const long ID_TX_NAME;
		static const long ID_TX_OBS;
		//*)

	private:
        std::unique_ptr<SQLite::Database> _database;

		//(*Handlers(WalletOverviewDialog)
		void OnlsWalletsSelect(wxCommandEvent& event);
		void OntxNameText(wxCommandEvent& event);
		void OntxObsText(wxCommandEvent& event);
		void OnbtEditClick(wxCommandEvent& event);
		void OnbtAddClick(wxCommandEvent& event);
		void OnbtRemoveClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
