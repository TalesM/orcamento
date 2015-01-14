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

        //(*Handlers(OrcamentoMainFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        void OnCreateBudget(wxCommandEvent& event);
        void OnExecuteBudget(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnlbMonthsDClick(wxCommandEvent& event);
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
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OrcamentoMainFrame)
        wxSimpleHtmlListBox* lbMonths;
        wxMenu* Menu3;
        wxMenuItem* mnNew;
        wxMenuItem* mnExecuteNextBudget;
        wxMenuItem* mnCreateBudget;
        wxStatusBar* StatusBar1;
        wxGrid* gdPromises;
        wxMenu* Menu5;
        wxMenu* Menu4;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ORCAMENTOMAINFRAME_H
