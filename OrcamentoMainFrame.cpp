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
const long OrcamentoMainFrame::ID_MENUITEM2 = wxNewId();
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
    wxMenu* Menu1;
    wxMenuItem* mnQuit;
    wxMenuItem* mnOpen;
    wxMenuBar* MenuBar1;
    wxSplitterWindow* SplitterWindow1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("OrcaMento"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,600));
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxPoint(152,304), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.25);
    lbMonths = new wxSimpleHtmlListBox(SplitterWindow1, ID_SIMPLEHTMLLISTBOX1, wxPoint(223,244), wxDefaultSize, 0, 0, wxHLB_DEFAULT_STYLE, wxDefaultValidator, _T("ID_SIMPLEHTMLLISTBOX1"));
    gdPromises = new wxGrid(SplitterWindow1, ID_GDPROMISES, wxPoint(78,4), wxDefaultSize, 0, _T("ID_GDPROMISES"));
    gdPromises->CreateGrid(0,6);
    gdPromises->HideCol(0);
    gdPromises->EnableEditing(true);
    gdPromises->EnableGridLines(true);
    gdPromises->SetColLabelValue(0, _("Id"));
    gdPromises->SetColLabelValue(1, _("Promise"));
    gdPromises->SetColLabelValue(2, _("Expected"));
    gdPromises->SetColLabelValue(3, _("Used"));
    gdPromises->SetColLabelValue(4, _("Due"));
    gdPromises->SetColLabelValue(5, _("Category"));
    gdPromises->SetDefaultCellFont( gdPromises->GetFont() );
    gdPromises->SetDefaultCellTextColour( gdPromises->GetForegroundColour() );
    SplitterWindow1->SplitVertically(lbMonths, gdPromises);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    mnNew = new wxMenuItem(Menu1, ID_MENUITEM1, _("New\tCtrl-N"), _("Create new Database"), wxITEM_NORMAL);
    mnNew->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW_DIR")),wxART_MENU));
    Menu1->Append(mnNew);
    mnOpen = new wxMenuItem(Menu1, ID_MENUITEM2, _("Open\tCtrl-O"), _("Open a database."), wxITEM_NORMAL);
    mnOpen->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_MENU));
    Menu1->Append(mnOpen);
    Menu1->AppendSeparator();
    mnQuit = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    mnQuit->SetBitmap(wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUIT")),wxART_MENU));
    Menu1->Append(mnQuit);
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

    Connect(ID_SIMPLEHTMLLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnlbMonthsDClick);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnNew);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnOpen);
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
        SQLite::Statement stm(*m_database, "SELECT name, executing, budget_id IN (SELECT max(budget_id) FROM budget WHERE budget.executing=1) FROM budget ORDER BY budget_id");
        while(stm.executeStep()){
            // TODO (Tales#1#): Mark currently active budget (an executing budget with next being NULL or a planing budget)
            wxString budgetName = wxString::FromUTF8(stm.getColumn(0));//
            bool executing = int(stm.getColumn(1));
            bool active = int(stm.getColumn(2));
            if(not executing){
                budgetName = "<em>" + budgetName + "</em>";
            } else if(active){
                budgetName = "<strong>" + budgetName + "</strong>";
            }
            lbMonths->Append(budgetName);
            if(active){
                lbMonths->SetSelection(lbMonths->GetCount()-1);
            }
        }
        RefreshPromises();
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshPromises()
{
    if(gdPromises->GetNumberRows()){
        gdPromises->DeleteRows(0, gdPromises->GetNumberRows());
    }
    int selected = lbMonths->GetSelection();
    if(selected >= 0){
        int budget_id = 1 + selected;
        try {
            const char *query = "SELECT promise_id, prom.name, prom.amount, 0, DATE(bud.start, prom.due), cat.name"
                                "  FROM budget bud JOIN promise prom USING(budget_id) LEFT JOIN category cat USING(category_id)"
                                "  WHERE budget_id = ?1 ORDER BY cat.name, prom.name"
            ;
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, budget_id);

            for(int i = 0; stm.executeStep(); ++i){
                gdPromises->AppendRows();
                gdPromises->SetCellValue({i, 0}, wxString::FromUTF8(stm.getColumn(0)) );
                gdPromises->SetCellValue({i, 1}, wxString::FromUTF8(stm.getColumn(1)) );
                gdPromises->SetCellValue({i, 2}, wxString::FromUTF8(stm.getColumn(2)) );
                gdPromises->SetCellValue({i, 3}, wxString::FromUTF8(stm.getColumn(3)) );
                gdPromises->SetCellValue({i, 4}, wxString::FromUTF8(stm.getColumn(4)) );
                gdPromises->SetCellValue({i, 5}, wxString::FromUTF8(stm.getColumn(5)) );
            }
            gdPromises->AutoSizeColumns();
        } catch (const std::exception &e){
            wxMessageBox(e.what());
        }
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
        try{
            m_database = std::unique_ptr<SQLite::Database>(new SQLite::Database(location, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
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

void OrcamentoMainFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, L"Select the file", "", "", "Orca files (*.orca)|*.orca", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if(openFileDialog.ShowModal() == wxCANCEL){
        return;
    }
    wxString location = openFileDialog.GetPath();
    try {
        m_database = std::unique_ptr<SQLite::Database>(new SQLite::Database(location, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
        RefreshModel();
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::OnlbMonthsDClick(wxCommandEvent& event)
{
    RefreshPromises();
}
