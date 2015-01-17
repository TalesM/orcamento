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

namespace PromiseColumn{
    constexpr int
        ID          = 0,
        NAME        = 1,
        ESTIMATED   = 2,
        ACCOUNTED   = 3,
        DUE         = 4,
        CATEGORY    = 5;
    constexpr int length = 6;
};

//(*IdInit(OrcamentoMainFrame)
const long OrcamentoMainFrame::ID_SIMPLEHTMLLISTBOX1 = wxNewId();
const long OrcamentoMainFrame::ID_GDPROMISES = wxNewId();
const long OrcamentoMainFrame::ID_SPLITTERWINDOW1 = wxNewId();
const long OrcamentoMainFrame::ID_MENUITEM1 = wxNewId();
const long OrcamentoMainFrame::ID_MENUITEM2 = wxNewId();
const long OrcamentoMainFrame::idMenuQuit = wxNewId();
const long OrcamentoMainFrame::ID_MENUCREATE_BUDGET = wxNewId();
const long OrcamentoMainFrame::ID_MENUEXECUTE_BUDGET = wxNewId();
const long OrcamentoMainFrame::ID_PROMISE_CREATE = wxNewId();
const long OrcamentoMainFrame::idMenuAbout = wxNewId();
const long OrcamentoMainFrame::ID_STATUSBAR1 = wxNewId();
const long OrcamentoMainFrame::ID_MENU_PROMISE_EDIT = wxNewId();
const long OrcamentoMainFrame::ID_MENUITEM4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OrcamentoMainFrame,wxFrame)
    //(*EventTable(OrcamentoMainFrame)
    //*)
END_EVENT_TABLE()

OrcamentoMainFrame::OrcamentoMainFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OrcamentoMainFrame)
    wxMenuItem* MenuItem2;
    wxMenu* Menu3;
    wxMenu* Menu1;
    wxMenuItem* mnQuit;
    wxMenuItem* mnOpen;
    wxMenuBar* MenuBar1;
    wxSplitterWindow* SplitterWindow1;
    wxMenu* Menu2;
    wxMenu* Menu5;

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
    gdPromises->SetColLabelValue(2, _("Estimated"));
    gdPromises->SetColLabelValue(3, _("Accounted"));
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
    mnPromise = new wxMenu();
    MenuItem1 = new wxMenuItem(mnPromise, ID_PROMISE_CREATE, _("Add a Promise\tCtrl-Insert"), _("Insert a new promise on current budget."), wxITEM_NORMAL);
    mnPromise->Append(MenuItem1);
    MenuBar1->Append(mnPromise, _("Promise"));
    Menu5 = new wxMenu();
    MenuBar1->Append(Menu5, _("Execution"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    sbStatus = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    sbStatus->SetFieldsCount(1,__wxStatusBarWidths_1);
    sbStatus->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(sbStatus);
    mnPromiseEdit = new wxMenuItem((&cmnPromise), ID_MENU_PROMISE_EDIT, _("Edit Promise"), wxEmptyString, wxITEM_NORMAL);
    cmnPromise.Append(mnPromiseEdit);
    MenuItem4 = new wxMenuItem((&cmnPromise), ID_MENUITEM4, _("Delete Promise"), wxEmptyString, wxITEM_NORMAL);
    cmnPromise.Append(MenuItem4);

    Connect(ID_SIMPLEHTMLLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnlbMonthsDClick);
    Connect(ID_GDPROMISES,wxEVT_GRID_CELL_RIGHT_CLICK,(wxObjectEventFunction)&OrcamentoMainFrame::OngdPromisesCellRightClick);
    Connect(ID_GDPROMISES,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&OrcamentoMainFrame::OngdPromisesCellChange);
    Connect(ID_GDPROMISES,wxEVT_GRID_SELECT_CELL,(wxObjectEventFunction)&OrcamentoMainFrame::OngdPromisesCellSelect);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnNew);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnOpen);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnQuit);
    Connect(ID_MENUCREATE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnCreateBudget);
    Connect(ID_MENUEXECUTE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnExecuteBudget);
    Connect(ID_PROMISE_CREATE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnCreatePromise);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnAbout);
    Connect(ID_MENU_PROMISE_EDIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnmnPromiseEditSelected);
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
            const char *query = "SELECT promise_id, prom.name, prom.amount/100.0, 0, DATE(bud.start, prom.due), cat.name"
                                "  FROM budget bud JOIN promise prom USING(budget_id) LEFT JOIN category cat USING(category_id)"
                                "  WHERE budget_id = ?1 ORDER BY category_id, prom.name"
            ;
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, budget_id);

            for(int i = 0; stm.executeStep(); ++i){
                gdPromises->AppendRows();
                for(int j = 0; j < PromiseColumn::length; ++j){
                    gdPromises->SetCellValue(i, j, wxString::FromUTF8(stm.getColumn(j)) );
                }
                if(stm.isColumnNull(PromiseColumn::CATEGORY)){
                    wxGridCellAttr *attrImultLine = new wxGridCellAttr();
                    attrImultLine->SetReadOnly(true);
                    gdPromises->SetRowAttr(i, attrImultLine);
                }
            }
            // TODO (Tales#1#): Modularize
            RefreshCellAttr();

        } catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    }
}

void OrcamentoMainFrame::RefreshCellAttr()
{
    auto moneyRenderer = new wxGridCellFloatRenderer(-1, 2);
    //Expected
    wxGridCellAttr *attrExpectedCol = new wxGridCellAttr();
    attrExpectedCol->SetRenderer(moneyRenderer);
    attrExpectedCol->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdPromises->SetColAttr(PromiseColumn::ESTIMATED, attrExpectedCol);

    //Spent
    moneyRenderer->IncRef();
    wxGridCellAttr *attrAccountedCol = new wxGridCellAttr();
    attrAccountedCol->SetReadOnly(true);
    attrAccountedCol->SetRenderer(moneyRenderer);
    gdPromises->SetColAttr(PromiseColumn::ACCOUNTED, attrAccountedCol);

    //Due
    wxGridCellAttr *attrDueCol = new wxGridCellAttr();
//            attrSpentCol->SetReadOnly(true);
    attrDueCol->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdPromises->SetColAttr(PromiseColumn::DUE, attrDueCol);

    //Category
    wxGridCellAttr *attrCategoryCol = new wxGridCellAttr();
    wxArrayString choices;
    SQLite::Statement choicesStm(*m_database, "SELECT name FROM category ORDER BY category_id ASC");
    while(choicesStm.executeStep()){
        choices.Add(wxString::FromUTF8(choicesStm.getColumn(0)));
    }
    attrCategoryCol->SetEditor(new wxGridCellChoiceEditor(choices));
    gdPromises->SetColAttr(PromiseColumn::CATEGORY, attrCategoryCol);
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

void OrcamentoMainFrame::OnCreatePromise(wxCommandEvent& event)
{
    int selection = lbMonths->GetSelection() + 1;
    if(!selection){
        return;
    }
    auto query = "INSERT INTO promise(budget_id, name, amount, category_id)"
                 "  VALUES (?1, 'New Promise', 0, (SELECT max(category_id) FROM category))";
    SQLite::Statement stm(*m_database, query);
    stm.bind(1, selection);
    if(!stm.exec()){
        wxMessageBox("Erro desconhecido");
    }

    RefreshPromises();
}

void OrcamentoMainFrame::OngdPromisesCellChange(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    wxString newValue = gdPromises->GetCellValue(row, col);
    if(event.GetString() == gdPromises->GetCellValue(row, col)){//The default editor duplicate events, so this avoids the first one.
        return;
    }
    long id;
    if(!gdPromises->GetCellValue(row, PromiseColumn::ID).ToCLong(&id)){
        wxMessageBox(L"Coluna Corrompida: '"+gdPromises->GetColLabelValue(0)+"'");
        return;
    }
    auto updateField = [this, id=int(id)](std::string field, const auto &value){
        try{
            std::string query = "UPDATE promise SET \""+field+"\" = ?2 WHERE promise_id = ?1";
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, id);
            stm.bind(2, value);
            if(!stm.exec()){
                wxMessageBox("Erro desconhecido");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    };
    switch(col){
    case PromiseColumn::NAME:
        updateField("name", newValue);
        break;
    case PromiseColumn::ESTIMATED:
        updateField("amount", int(atof(newValue)*100));
        break;
    case PromiseColumn::DUE:
        try{
            wxDateTime due{};
            due.ParseISODate(newValue);
            int day = due.GetDay() -1;
            std::string query = "UPDATE promise SET \"due\" = ?2|| ' days' WHERE promise_id = ?1";
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, int(id));
            stm.bind(2, day);
            if(!stm.exec()){
                wxMessageBox("Erro desconhecido");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        break;
    case PromiseColumn::CATEGORY:
        try{
            std::string query = "UPDATE promise SET \"category_id\" = (SELECT category_id FROM category WHERE name=?2) WHERE promise_id = ?1";
            SQLite::Statement stm(*m_database, query);
            stm.bind(1, int(id));
            stm.bind(2, newValue);
            if(!stm.exec()){
                wxMessageBox("Erro desconhecido");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        break;
    default:
        break;
    }
}

void OrcamentoMainFrame::OngdPromisesCellSelect(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    if(row > 0 and col == PromiseColumn::ACCOUNTED){
        wxMessageBox("OIE!");
    }
}

void OrcamentoMainFrame::OngdPromisesCellRightClick(wxGridEvent& event)
{
    wxPoint point = event.GetPosition();
    wxGridCellCoords coords(event.GetRow(), event.GetCol());
    if(coords.GetRow() < 1){
        return;
    }

    cmnPromise.SetClientData(&coords);
    gdPromises->GetPosition();
    PopupMenu( &cmnPromise, gdPromises->GetPosition() + point);
    cmnPromise.SetClientData(NULL);
}

void OrcamentoMainFrame::OnmnPromiseEditSelected(wxCommandEvent& event)
{
    if(cmnPromise.GetClientData()){
        wxGridCellCoords &coords = *reinterpret_cast<wxGridCellCoords*>(cmnPromise.GetClientData());
        wxString str(L"Happened at ");
        str << coords.GetRow() << ", " << coords.GetCol();
        wxMessageBox(str);
    }
}
