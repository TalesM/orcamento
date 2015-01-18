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
#include "ExecutionDialog.h"
#include "WalletOverviewDialog.h"
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

namespace EstimateColumn{
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
const long OrcamentoMainFrame::ID_MENUITEM5 = wxNewId();
const long OrcamentoMainFrame::idMenuAbout = wxNewId();
const long OrcamentoMainFrame::ID_STATUSBAR1 = wxNewId();
const long OrcamentoMainFrame::ID_MENU_PROMISE_EDIT = wxNewId();
const long OrcamentoMainFrame::ID_MENUITEM3 = wxNewId();
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
    wxMenuItem* mnWalletsOverview;
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
    gdEstimates = new wxGrid(SplitterWindow1, ID_GDPROMISES, wxPoint(78,4), wxDefaultSize, 0, _T("ID_GDPROMISES"));
    gdEstimates->CreateGrid(0,6);
    gdEstimates->HideCol(0);
    gdEstimates->EnableEditing(true);
    gdEstimates->EnableGridLines(true);
    gdEstimates->SetColLabelValue(0, _("Id"));
    gdEstimates->SetColLabelValue(1, _("Name"));
    gdEstimates->SetColLabelValue(2, _("Estimated"));
    gdEstimates->SetColLabelValue(3, _("Accounted"));
    gdEstimates->SetColLabelValue(4, _("Due"));
    gdEstimates->SetColLabelValue(5, _("Category"));
    gdEstimates->SetDefaultCellFont( gdEstimates->GetFont() );
    gdEstimates->SetDefaultCellTextColour( gdEstimates->GetForegroundColour() );
    SplitterWindow1->SplitVertically(lbMonths, gdEstimates);
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
    mnCreateBudget = new wxMenuItem(Menu3, ID_MENUCREATE_BUDGET, _("Create Next Budget\tAlt-b"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnCreateBudget);
    mnExecuteNextBudget = new wxMenuItem(Menu3, ID_MENUEXECUTE_BUDGET, _("Execute Next Budget"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(mnExecuteNextBudget);
    MenuBar1->Append(Menu3, _("Budget"));
    mnEstimate = new wxMenu();
    MenuItem1 = new wxMenuItem(mnEstimate, ID_PROMISE_CREATE, _("Add a Estimate\tAlt-Insert"), _("Insert a new estimate on current budget."), wxITEM_NORMAL);
    mnEstimate->Append(MenuItem1);
    MenuBar1->Append(mnEstimate, _("Estimate"));
    Menu5 = new wxMenu();
    mnWalletsOverview = new wxMenuItem(Menu5, ID_MENUITEM5, _("Overview\tAlt-w"), wxEmptyString, wxITEM_NORMAL);
    Menu5->Append(mnWalletsOverview);
    MenuBar1->Append(Menu5, _("Wallet"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    sbStatus = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[4] = { -1, -1, -1, -1 };
    int __wxStatusBarStyles_1[4] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    sbStatus->SetFieldsCount(4,__wxStatusBarWidths_1);
    sbStatus->SetStatusStyles(4,__wxStatusBarStyles_1);
    SetStatusBar(sbStatus);
    mnEstimateEdit = new wxMenuItem((&cmnEstimate), ID_MENU_PROMISE_EDIT, _("Detail"), wxEmptyString, wxITEM_NORMAL);
    cmnEstimate.Append(mnEstimateEdit);
    mnExecute = new wxMenuItem((&cmnEstimate), ID_MENUITEM3, _("Execute"), wxEmptyString, wxITEM_NORMAL);
    cmnEstimate.Append(mnExecute);
    mnExecute->Enable(false);
    cmnEstimate.AppendSeparator();
    MenuItem4 = new wxMenuItem((&cmnEstimate), ID_MENUITEM4, _("Delete Estimate"), wxEmptyString, wxITEM_NORMAL);
    cmnEstimate.Append(MenuItem4);

    Connect(ID_SIMPLEHTMLLISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnlbMonthsDClick);
    Connect(ID_GDPROMISES,wxEVT_GRID_CELL_RIGHT_CLICK,(wxObjectEventFunction)&OrcamentoMainFrame::OngdEstimatesCellRightClick);
    Connect(ID_GDPROMISES,wxEVT_GRID_CELL_LEFT_DCLICK,(wxObjectEventFunction)&OrcamentoMainFrame::OngdEstimatesCellLeftDClick);
    Connect(ID_GDPROMISES,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&OrcamentoMainFrame::OngdEstimatesCellChange);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnNew);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnOpen);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnQuit);
    Connect(ID_MENUCREATE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnCreateBudget);
    Connect(ID_MENUEXECUTE_BUDGET,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnExecuteBudget);
    Connect(ID_PROMISE_CREATE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnCreateEstimate);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnWalletsOverview);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnAbout);
    Connect(ID_MENU_PROMISE_EDIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnmnEstimateEditSelected);
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
        SQLite::Statement stm(*_database, "SELECT name, executing, budget_id IN (SELECT max(budget_id) FROM budget WHERE budget.executing=1) FROM budget ORDER BY budget_id");
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
        RefreshEstimates();
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshEstimates()
{
    if(gdEstimates->GetNumberRows()){
        gdEstimates->DeleteRows(0, gdEstimates->GetNumberRows());
    }
    int selected = lbMonths->GetSelection();
    if(selected >= 0){
        int budget_id = 1 + selected;
        try {
            const char *query = "SELECT estimate_id, prom.name, prom.amount/100.0, 0, DATE(bud.start, prom.due), cat.name"
                                "  FROM budget bud JOIN estimate prom USING(budget_id) LEFT JOIN category cat USING(category_id)"
                                "  WHERE budget_id = ?1 ORDER BY category_id, prom.name";
            SQLite::Statement stm(*_database, query);
            stm.bind(1, budget_id);

            for(int i = 0; stm.executeStep(); ++i){
                gdEstimates->AppendRows();
                for(int j = 0; j < EstimateColumn::length; ++j){
                    gdEstimates->SetCellValue(i, j, wxString::FromUTF8(stm.getColumn(j)) );
                }
                if(stm.isColumnNull(EstimateColumn::CATEGORY)){
                    wxGridCellAttr *attrImultLine = new wxGridCellAttr();
                    attrImultLine->SetReadOnly(true);
                    gdEstimates->SetRowAttr(i, attrImultLine);
                }
            }
            // TODO (Tales#1#): Modularize
            RefreshCellAttr();

        } catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    }
}

void OrcamentoMainFrame::RefreshStatusBar()
{
    int budget_id = lbMonths->GetSelection()+1;
    if(budget_id < 1){
        return;
    }
    try{
        const char *query = "SELECT budget.name, SUM(estimate.amount)/100.0, IFNULL(SUM(execution.amount)/100.0, 0.00)"
                            "  FROM budget"
                            "  JOIN estimate USING(budget_id)"
                            "  LEFT JOIN execution USING(estimate_id)"
                            "  WHERE budget_id = ?1"
        ;
        SQLite::Statement stm(*_database, query);
        stm.bind(1, budget_id);
        if(!stm.executeStep()){
            wxMessageBox("ERROR?");
        }
        sbStatus->SetStatusText(L"Budget: " + wxString::FromUTF8(stm.getColumn(0)), 1);
        sbStatus->SetStatusText(L"Estimated: " + wxString::FromUTF8(stm.getColumn(1)), 2);
        sbStatus->SetStatusText(L"Accounted: " + wxString::FromUTF8(stm.getColumn(2)), 3);
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}


void OrcamentoMainFrame::RefreshCellAttr()
{
    auto moneyRenderer = new wxGridCellFloatRenderer(-1, 2);
    //Expected
    wxGridCellAttr *attrExpectedCol = new wxGridCellAttr();
    attrExpectedCol->SetRenderer(moneyRenderer);
    attrExpectedCol->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdEstimates->SetColAttr(EstimateColumn::ESTIMATED, attrExpectedCol);

    //Spent
    moneyRenderer->IncRef();
    wxGridCellAttr *attrAccountedCol = new wxGridCellAttr();
    attrAccountedCol->SetReadOnly(true);
    attrAccountedCol->SetRenderer(moneyRenderer);
    gdEstimates->SetColAttr(EstimateColumn::ACCOUNTED, attrAccountedCol);

    //Due
    wxGridCellAttr *attrDueCol = new wxGridCellAttr();
    attrDueCol->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdEstimates->SetColAttr(EstimateColumn::DUE, attrDueCol);

    //Category
    wxGridCellAttr *attrCategoryCol = new wxGridCellAttr();
    wxArrayString choices;
    SQLite::Statement choicesStm(*_database, "SELECT name FROM category ORDER BY category_id ASC");
    while(choicesStm.executeStep()){
        choices.Add(wxString::FromUTF8(choicesStm.getColumn(0)));
    }
    attrCategoryCol->SetEditor(new wxGridCellChoiceEditor(choices));
    gdEstimates->SetColAttr(EstimateColumn::CATEGORY, attrCategoryCol);
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
            _database = std::unique_ptr<SQLite::Database>(new SQLite::Database(location, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
            SQLite::Transaction transaction(*_database);
            _database->exec(model);

            auto query = "INSERT INTO budget(name, start, duration)"
                         "  VALUES (strftime('%m/%Y', ?1), date(?1, 'start of month'), '1 months')";
            SQLite::Statement stm(*_database, query);
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
        if(!_database->exec("INSERT INTO budget(name, start, duration) "
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
        if(!_database->exec("UPDATE budget SET executing = 1"
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
        _database = std::unique_ptr<SQLite::Database>(new SQLite::Database(location, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE));
        RefreshModel();
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::OnlbMonthsDClick(wxCommandEvent& event)
{
    RefreshEstimates();
    RefreshStatusBar();
}

void OrcamentoMainFrame::OnCreateEstimate(wxCommandEvent& event)
{
    int selection = lbMonths->GetSelection() + 1;
    if(!selection){
        return;
    }
    auto query = "INSERT INTO estimate(budget_id, name, amount, category_id)"
                 "  VALUES (?1, 'New Estimate', 0, (SELECT max(category_id) FROM category))";
    SQLite::Statement stm(*_database, query);
    stm.bind(1, selection);
    if(!stm.exec()){
        wxMessageBox("Erro desconhecido");
    }

    RefreshEstimates();
}

void OrcamentoMainFrame::OngdEstimatesCellChange(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    wxString newValue = gdEstimates->GetCellValue(row, col);
    if(event.GetString() == gdEstimates->GetCellValue(row, col)){//The default editor duplicate events, so this avoids the first one.
        return;
    }
    long id;
    if(!gdEstimates->GetCellValue(row, EstimateColumn::ID).ToCLong(&id)){
        wxMessageBox(L"Coluna Corrompida: '"+gdEstimates->GetColLabelValue(0)+"'");
        return;
    }
    auto updateField = [this, id=int(id)](std::string field, const auto &value){
        try{
            std::string query = "UPDATE estimate SET \""+field+"\" = ?2 WHERE estimate_id = ?1";
            SQLite::Statement stm(*_database, query);
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
    case EstimateColumn::NAME:
        updateField("name", newValue);
        break;
    case EstimateColumn::ESTIMATED:
        updateField("amount", int(atof(newValue)*100));
        RefreshStatusBar();
        break;
    case EstimateColumn::DUE:
        try{
            wxDateTime due{};
            due.ParseISODate(newValue);
            int day = due.GetDay() -1;
            std::string query = "UPDATE estimate SET \"due\" = ?2|| ' days' WHERE estimate_id = ?1";
            SQLite::Statement stm(*_database, query);
            stm.bind(1, int(id));
            stm.bind(2, day);
            if(!stm.exec()){
                wxMessageBox("Erro desconhecido");
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        break;
    case EstimateColumn::CATEGORY:
        try{
            std::string query = "UPDATE estimate SET \"category_id\" = (SELECT category_id FROM category WHERE name=?2) WHERE estimate_id = ?1";
            SQLite::Statement stm(*_database, query);
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

void OrcamentoMainFrame::OngdEstimatesCellRightClick(wxGridEvent& event)
{
    wxPoint point = event.GetPosition();
    wxGridCellCoords coords(event.GetRow(), event.GetCol());
    if(coords.GetRow() < 1){
        return;
    }

    cmnEstimate.SetClientData(&coords);
    gdEstimates->GetPosition();
    PopupMenu( &cmnEstimate, gdEstimates->GetPosition() + point);
    cmnEstimate.SetClientData(NULL);
}

void OrcamentoMainFrame::OnmnEstimateEditSelected(wxCommandEvent& event)
{
    if(cmnEstimate.GetClientData()){
        wxGridCellCoords &coords = *reinterpret_cast<wxGridCellCoords*>(cmnEstimate.GetClientData());
        wxString str(L"Happened at ");
        str << coords.GetRow() << ", " << coords.GetCol();
        wxMessageBox(str);
    }
}

void OrcamentoMainFrame::OnWalletsOverview(wxCommandEvent& event)
{
    WalletOverviewDialog overview(this);
    overview.giveDatabase(_database);
    overview.ShowModal();
    _database = overview.takeDatabase();
}

void OrcamentoMainFrame::OngdEstimatesCellLeftDClick(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    if(row > 0 and col == EstimateColumn::ACCOUNTED){
        ExecutionDialog executionDialog(this, wxID_ANY, atoi(gdEstimates->GetCellValue(row, 0)));
        executionDialog.giveDatabase(_database);
        executionDialog.ShowModal();
        _database = executionDialog.takeDatabase();
    }
}
