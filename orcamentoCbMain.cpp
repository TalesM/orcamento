/***************************************************************
 * Name:      orcamentoCbMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "orcamentoCbMain.h"
#include "NewDatabaseDialog.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(orcamentoCbFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(orcamentoCbFrame)
const long orcamentoCbFrame::idMenuNew = wxNewId();
const long orcamentoCbFrame::idMenuQuit = wxNewId();
const long orcamentoCbFrame::idMenuAbout = wxNewId();
const long orcamentoCbFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(orcamentoCbFrame,wxFrame)
    //(*EventTable(orcamentoCbFrame)
    //*)
END_EVENT_TABLE()

orcamentoCbFrame::orcamentoCbFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(orcamentoCbFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuNew, _("New\tCtrl-N"), _("Create new Database"), wxITEM_NORMAL);
    MenuItem3->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW_DIR")),wxART_MENU));
    Menu1->Append(MenuItem3);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuBar1->Append(Menu3, _("Budget"));
    Menu4 = new wxMenu();
    MenuBar1->Append(Menu4, _("Promise"));
    Menu5 = new wxMenu();
    MenuBar1->Append(Menu5, _("Execution"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuNew,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&orcamentoCbFrame::OnNew);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&orcamentoCbFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&orcamentoCbFrame::OnAbout);
    //*)
}

orcamentoCbFrame::~orcamentoCbFrame()
{
    //(*Destroy(orcamentoCbFrame)
    //*)
}

void orcamentoCbFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void orcamentoCbFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void orcamentoCbFrame::OnNew(wxCommandEvent& event)
{
    NewDatabaseDialog dialog(this);
    if ( dialog.ShowModal() == wxID_OK ){
        wxMessageBox(_("Loaded"));
        m_database = std::unique_ptr<SQLite::Database>(new SQLite::Database("Teste.orca", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
        m_database->exec("DROP TABLE IF EXISTS test");

        // Begin transaction
        SQLite::Transaction transaction(*m_database);

        m_database->exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

        int nb = m_database->exec("INSERT INTO test VALUES (NULL, \"test\")");
        std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

        // Commit transaction
        transaction.commit();
    } else {
        wxMessageBox(_("Failed"));
    }
}
