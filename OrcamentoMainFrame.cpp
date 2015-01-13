/***************************************************************
 * Name:      orcamentoCbMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    TalesM (tales.miranda88@gmail.com)
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "OrcamentoMainFrame.h"
#include "CreateDatabaseDialog.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OrcamentoMainFrame)
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

//(*IdInit(OrcamentoMainFrame)
const long OrcamentoMainFrame::ID_SIMPLEHTMLLISTBOX1 = wxNewId();
const long OrcamentoMainFrame::ID_GDPROMISES = wxNewId();
const long OrcamentoMainFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long OrcamentoMainFrame::ID_MENUITEM1 = wxNewId();
const long OrcamentoMainFrame::idMenuQuit = wxNewId();
const long OrcamentoMainFrame::ID_MENUCREATE_BUDGET = wxNewId();
const long OrcamentoMainFrame::ID_MENUEXECUTE_BUDGET = wxNewId();
const long OrcamentoMainFrame::idMenuAbout = wxNewId();
const long OrcamentoMainFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OrcamentoMainFrame,wxFrame)
    //(*EventTable(OrcamentoMainFrame)
    //*)
END_EVENT_TABLE()

OrcamentoMainFrame::OrcamentoMainFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OrcamentoMainFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxSplitterWindow* SplitterWindow1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxPoint(152,304), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.25);
    lbMonths = new wxSimpleHtmlListBox(SplitterWindow1, ID_SIMPLEHTMLLISTBOX1, wxPoint(223,244), wxDefaultSize, 0, 0, wxHLB_DEFAULT_STYLE, wxDefaultValidator, _T("ID_SIMPLEHTMLLISTBOX1"));
    gdPromises = new wxGrid(SplitterWindow1, ID_GDPROMISES, wxPoint(78,4), wxDefaultSize, 0, _T("ID_GDPROMISES"));
    gdPromises->CreateGrid(0,5);
    gdPromises->EnableEditing(true);
    gdPromises->EnableGridLines(true);
    gdPromises->SetDefaultCellFont( gdPromises->GetFont() );
    gdPromises->SetDefaultCellTextColour( gdPromises->GetForegroundColour() );
    SplitterWindow1->SplitVertically(lbMonths, gdPromises);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("New\tCtrl-N"), _("Create new Database"), wxITEM_NORMAL);
    MenuItem3->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW_DIR")),wxART_MENU));
    Menu1->Append(MenuItem3);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    mnCreateBudget = new wxMenuItem(Menu3, ID_MENUCREATE_BUDGET, _("Create Next Budget"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCreateBudget);
    mnExecuteNextBudget = new wxMenuItem(Menu3, ID_MENUEXECUTE_BUDGET, _("Execute Next Budget"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnExecuteNextBudget);
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

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnNew);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnQuit);
    Connect(ID_MENUCREATE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnCreateBudget);
    Connect(ID_MENUEXECUTE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnExecuteBudget);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnAbout);
    //*)
}

OrcamentoMainFrame::~OrcamentoMainFrame()
{
    //(*Destroy(OrcamentoMainFrame)
    //*)
}

void OrcamentoMainFrame::RefreshModel()
{
    lbMonths->Clear();
    try {
        SQLite::Statement stm(*m_database, "SELECT bud.name, bud.executing FROM budget bud ORDER BY bud.budget_id");
        while(stm.executeStep()){
            // TODO (Tales#1#): Mark currently active budget (an executing budget with next being NULL or a planing budget)
            wxString budgetName = wxString::FromUTF8(stm.getColumn(0));//
            bool executing = int(stm.getColumn(1));
            if(not executing){
                budgetName = "<em>" + budgetName + "</em>";
            }
            lbMonths->Append(budgetName);
        }
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OrcamentoMainFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OrcamentoMainFrame::OnNew(wxCommandEvent& event)
{
    CreateDatabaseDialog dialog(this);
    if(dialog.ShowModal() != wxID_OK ){
        return;
    }
    wxString location = dialog.getLocation();
    wxDateTime start  = dialog.getStart();

    // Begin transaction
    wxString model;
    wxFile modelFile(L"theModel.sql");
    if(modelFile.ReadAll(&model)){
        m_database = std::unique_ptr<SQLite::Database>(new SQLite::Database(location, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
        try{
            SQLite::Transaction transaction(*m_database);
            m_database->exec(model);

            auto query = "INSERT INTO budget(name, start, duration)"
                         "  VALUES (strftime('%m/%Y', ?1), date(?1, 'start of month'), '1 months')";
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, start.FormatISODate().ToUTF8());
            stm.exec();

            // Commit transaction
            transaction.commit();
        } catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        RefreshModel();
    }
}

void OrcamentoMainFrame::OnCreateBudget(wxCommandEvent& event)
{
    if(wxMessageBox(L"Are you sure you want to create a new Budget?", L"Create Budget", wxYES_NO|wxCENTRE) != wxYES){
        return;
    }
    try{
        if(!m_database->exec("INSERT INTO budget(name, start, duration) "
                             "  SELECT strftime('%m/%Y', start, duration), date(start, duration), duration "
                             "    FROM budget WHERE budget_id IN (SELECT max(budget_id) FROM budget)")
        ){
            wxMessageBox("The total universe time expired :(");
        }
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
    RefreshModel();
}

void OrcamentoMainFrame::OnExecuteBudget(wxCommandEvent& event)
{
    if(wxMessageBox(L"Are you sure you want to execute the next Budget?", L"Execute Budget", wxYES_NO|wxCENTRE) != wxYES){
        return;
    }
    try{
        if(!m_database->exec("UPDATE budget SET executing = 1"
                             "  WHERE budget_id IN (SELECT min(budget_id)"
                             "  FROM budget WHERE executing=0)"
        )){
            wxMessageBox("The total universe time expired :(");
        }
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
    RefreshModel();
}
