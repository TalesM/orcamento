/***************************************************************
 * Name:      orcamentoCbMain.h
 * Purpose:   Defines Application Frame
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#ifndef ORCAMENTOMAINFRAME_H
#define ORCAMENTOMAINFRAME_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
//(*Headers(OrcamentoMainFrame)
#include <wx/menu.h>
#include <wx/htmllbox.h>
#include <wx/splitter.h>
#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class OrcamentoMainFrame: public wxFrame
{
    public:

        OrcamentoMainFrame(wxWindow* parent,wxWindowID id = -1);

        virtual ~OrcamentoMainFrame();

    private:
        std::unique_ptr<SQLite::Database> _database;

        void RefreshModel();
        void RefreshEstimates();
        void RefreshCellAttr();
        void RefreshStatusBar();

        //(*Handlers(OrcamentoMainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        void OnCreateBudget(wxCommandEvent& event);
        void OnExecuteBudget(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnlbMonthsDClick(wxCommandEvent& event);
        void OnCreateEstimate(wxCommandEvent& event);
        void OngdEstimatesCellChange(wxGridEvent& event);
        void OngdEstimatesCellSelect(wxGridEvent& event);
        void OngdEstimatesCellRightClick(wxGridEvent& event);
        void OnmnEstimateEditSelected(wxCommandEvent& event);
        void OnWalletsOverview(wxCommandEvent& event);
        //*)

        //(*Identifiers(OrcamentoMainFrame)
        static const long ID_SIMPLEHTMLLISTBOX1;
        static const long ID_GDPROMISES;
        static const long ID_SPLITTERWINDOW1;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long idMenuQuit;
        static const long ID_MENUCREATE_BUDGET;
        static const long ID_MENUEXECUTE_BUDGET;
        static const long ID_PROMISE_CREATE;
        static const long ID_MENUITEM5;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_MENU_PROMISE_EDIT;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM4;
        //*)

        //(*Declarations(OrcamentoMainFrame)
        wxMenuItem* mnExecute;
        wxSimpleHtmlListBox* lbMonths;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem4;
        wxGrid* gdEstimates;
        wxMenuItem* mnNew;
        wxMenuItem* mnExecuteNextBudget;
        wxMenuItem* mnCreateBudget;
        wxMenu* mnEstimate;
        wxStatusBar* sbStatus;
        wxMenu cmnEstimate;
        wxMenuItem* mnEstimateEdit;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ORCAMENTOMAINFRAME_H
