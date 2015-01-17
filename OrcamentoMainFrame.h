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
        std::unique_ptr<SQLite::Database> m_database;

        void RefreshModel();
        void RefreshPromises();
        void RefreshCellAttr();

        //(*Handlers(OrcamentoMainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        void OnCreateBudget(wxCommandEvent& event);
        void OnExecuteBudget(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnlbMonthsDClick(wxCommandEvent& event);
        void OnCreatePromise(wxCommandEvent& event);
        void OngdPromisesCellChange(wxGridEvent& event);
        void OngdPromisesCellSelect(wxGridEvent& event);
        void OngdPromisesCellRightClick(wxGridEvent& event);
        void OnmnPromiseEditSelected(wxCommandEvent& event);
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
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_MENU_PROMISE_EDIT;
        static const long ID_MENUITEM4;
        //*)

        //(*Declarations(OrcamentoMainFrame)
        wxSimpleHtmlListBox* lbMonths;
        wxMenuItem* MenuItem1;
        wxMenuItem* MenuItem4;
        wxMenuItem* mnNew;
        wxMenuItem* mnExecuteNextBudget;
        wxMenu cmnPromise;
        wxMenuItem* mnCreateBudget;
        wxStatusBar* sbStatus;
        wxMenuItem* mnPromiseEdit;
        wxMenu* mnPromise;
        wxGrid* gdPromises;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ORCAMENTOMAINFRAME_H
