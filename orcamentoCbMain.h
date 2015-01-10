/***************************************************************
 * Name:      orcamentoCbMain.h
 * Purpose:   Defines Application Frame
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#ifndef ORCAMENTOCBMAIN_H
#define ORCAMENTOCBMAIN_H

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
//(*Headers(orcamentoCbFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class orcamentoCbFrame: public wxFrame
{
    public:

        orcamentoCbFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~orcamentoCbFrame();

    private:
        std::unique_ptr<SQLite::Database> m_database;


        //(*Handlers(orcamentoCbFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnNew(wxCommandEvent& event);
        //*)

        //(*Identifiers(orcamentoCbFrame)
        static const long idMenuNew;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(orcamentoCbFrame)
        wxMenu* Menu3;
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        wxMenu* Menu5;
        wxMenu* Menu4;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ORCAMENTOCBMAIN_H
