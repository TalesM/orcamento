/***************************************************************
 * Name:      orcamentoMainFrame.cpp
 * Purpose:   Code for Application Frame
 * Author:    TalesM
 * Created:   2015-01-10
 * Copyright: TalesM (talesm.github.io)
 * License:   GPL3 - See license.txt
 **************************************************************/

#include "wx_pch.h"
#include "OrcamentoMainFrame.h"

#include <string>
#include <vector>
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include "CreateDatabaseDialog.h"
#include "ExecutionDialog.h"
#include "WalletOverviewDialog.h"

//(*InternalHeaders(OrcamentoMainFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    if (format == long_f )
    {
        wxString wxbuild;
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
        return wxbuild;
    }
    return wxVERSION_STRING;
}

inline wxString isoDate(){
    wxString date(__DATE__), time(__TIME__);
    wxDateTime isoDate;
    isoDate.ParseFormat(date+" "+time, "%b %d %Y %T");
    return isoDate.FormatISOCombined();
}

namespace EstimateColumn{
    constexpr int
        ID          = 0,
        NAME        = 1,
        DUE         = 2,
        ESTIMATED   = 3,
        ACCOUNTED   = 4,
        REMAINING   = 5,
        CATEGORY    = 6,
        OBS         = 7;
    constexpr int length = 8;
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
const long OrcamentoMainFrame::ID_MENU_ESTIMATE_EDIT = wxNewId();
const long OrcamentoMainFrame::ID_MENU_ESTIMATE_COPYSELECTEDTO = wxNewId();
const long OrcamentoMainFrame::ID_MENU_ESTIMATE_DELETE = wxNewId();
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
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("orca_1.ico"))));
    	SetIcon(FrameIcon);
    }
    SplitterWindow1 = new wxSplitterWindow(this, ID_SPLITTERWINDOW1, wxPoint(152,304), wxDefaultSize, wxSP_3D, _T("ID_SPLITTERWINDOW1"));
    SplitterWindow1->SetMinSize(wxSize(10,10));
    SplitterWindow1->SetMinimumPaneSize(10);
    SplitterWindow1->SetSashGravity(0.25);
    lbMonths = new wxSimpleHtmlListBox(SplitterWindow1, ID_SIMPLEHTMLLISTBOX1, wxPoint(223,244), wxDefaultSize, 0, 0, wxHLB_DEFAULT_STYLE, wxDefaultValidator, _T("ID_SIMPLEHTMLLISTBOX1"));
    gdEstimates = new wxGrid(SplitterWindow1, ID_GDPROMISES, wxPoint(78,4), wxDefaultSize, 0, _T("ID_GDPROMISES"));
    gdEstimates->CreateGrid(0,8);
    gdEstimates->HideCol(0);
    gdEstimates->EnableEditing(true);
    gdEstimates->EnableGridLines(true);
    gdEstimates->SetColLabelValue(0, _("Id"));
    gdEstimates->SetColLabelValue(1, _("Name"));
    gdEstimates->SetColLabelValue(2, _("Due"));
    gdEstimates->SetColLabelValue(3, _("Estimated"));
    gdEstimates->SetColLabelValue(4, _("Accounted"));
    gdEstimates->SetColLabelValue(5, _("Remaining"));
    gdEstimates->SetColLabelValue(6, _("Category"));
    gdEstimates->SetColLabelValue(7, _("Observation"));
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
    int __wxStatusBarWidths_1[5] = { -2, -1, -1, -1, -1 };
    int __wxStatusBarStyles_1[5] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    sbStatus->SetFieldsCount(5,__wxStatusBarWidths_1);
    sbStatus->SetStatusStyles(5,__wxStatusBarStyles_1);
    SetStatusBar(sbStatus);
    mnEstimateEdit = new wxMenuItem((&cmnEstimate), ID_MENU_ESTIMATE_EDIT, _("Execute"), wxEmptyString, wxITEM_NORMAL);
    cmnEstimate.Append(mnEstimateEdit);
    mnEstimateCopySelectedTo = new wxMenuItem((&cmnEstimate), ID_MENU_ESTIMATE_COPYSELECTEDTO, _("Copy Selected Rows to...\tCtrl-Alt-p"), _("Copies all selected rows to anothe budget."), wxITEM_NORMAL);
    cmnEstimate.Append(mnEstimateCopySelectedTo);
    cmnEstimate.AppendSeparator();
    mnEstimateDelete = new wxMenuItem((&cmnEstimate), ID_MENU_ESTIMATE_DELETE, _("Delete Estimate"), wxEmptyString, wxITEM_NORMAL);
    cmnEstimate.Append(mnEstimateDelete);

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
    Connect(ID_MENU_ESTIMATE_EDIT,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnmnEstimateEditSelected);
    Connect(ID_MENU_ESTIMATE_COPYSELECTEDTO,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnmnEstimateCopySelectedToSelected);
    Connect(ID_MENU_ESTIMATE_DELETE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OrcamentoMainFrame::OnmnEstimateDeleteSelected);
    //*)

    SetupCellAttr();
}

OrcamentoMainFrame::~OrcamentoMainFrame()
{
    //(*Destroy(OrcamentoMainFrame)
    //*)
}

void OrcamentoMainFrame::SetupCellAttr()
{
    auto moneyRenderer = new wxGridCellFloatRenderer(-1, 2);
    //Due
    wxGridCellAttr *attrDueCol = new wxGridCellAttr();
    attrDueCol->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdEstimates->SetColAttr(EstimateColumn::DUE, attrDueCol);

    //Expected
    wxGridCellAttr *attrExpectedCol = new wxGridCellAttr();
    attrExpectedCol->SetRenderer(moneyRenderer);
    attrExpectedCol->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdEstimates->SetColAttr(EstimateColumn::ESTIMATED, attrExpectedCol);

    //Accounted
    moneyRenderer->IncRef();
    wxGridCellAttr *attrAccountedCol = new wxGridCellAttr();
    attrAccountedCol->SetReadOnly(true);
    attrAccountedCol->SetRenderer(moneyRenderer);
    gdEstimates->SetColAttr(EstimateColumn::ACCOUNTED, attrAccountedCol);

    //Remaining
    moneyRenderer->IncRef();
    wxGridCellAttr *attrRemainingCol = new wxGridCellAttr();
    attrRemainingCol->SetReadOnly(true);
    attrRemainingCol->SetRenderer(moneyRenderer);
    gdEstimates->SetColAttr(EstimateColumn::REMAINING, attrRemainingCol);

    //OBS
    wxGridCellAttr *obsCol = new wxGridCellAttr();
    obsCol->SetReadOnly();
    gdEstimates->SetColAttr(EstimateColumn::OBS, obsCol);
}


void OrcamentoMainFrame::RefreshModel()
{
    lbMonths->Clear();
    try {
        _activeIndex = -1;
        _document->look(_budgetView, [this](std::string name, int executing, int active){
            wxString budgetName(wxString::FromUTF8(name.c_str()));
            if(not executing){
                budgetName = "<em>" + budgetName + "</em>";
            } else if(active){
                budgetName = "<strong>" + budgetName + "</strong>";
                _activeIndex = lbMonths->GetCount();
            }
            lbMonths->Append(budgetName);
            if(active){
                lbMonths->SetSelection(lbMonths->GetCount()-1);
            }
        });
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
    int budget_id = lbMonths->GetSelection() + 1;
    if(budget_id <= 0){
        return;
    }
    try {
        int i = 0;
        auto refreshFunction = [this, &i](int id,
                                          std::string name,
                                          std::string due,
                                          double estimated,
                                          double accounted,
                                          double remaining,
                                          std::string category,
                                          std::string obs){
            gdEstimates->AppendRows();
            gdEstimates->SetCellValue(i, EstimateColumn::ID,
                                      wxString::FromDouble(id));
            gdEstimates->SetCellValue(i, EstimateColumn::NAME,
                                      wxString::FromUTF8(name.c_str()));
            gdEstimates->SetCellValue(i, EstimateColumn::DUE,
                                      wxString::FromUTF8(due.c_str()));
            gdEstimates->SetCellValue(i, EstimateColumn::ESTIMATED,
                                      wxString::FromDouble(estimated));            gdEstimates->SetCellValue(i, EstimateColumn::ACCOUNTED,
                                      wxString::FromDouble(accounted) );
            gdEstimates->SetCellValue(i, EstimateColumn::REMAINING,
                                      wxString::FromDouble(remaining) );
            gdEstimates->SetCellValue(i, EstimateColumn::CATEGORY,
                                      wxString::FromUTF8(category.c_str()) );
            gdEstimates->SetCellValue(i, EstimateColumn::OBS,
                                      wxString::FromUTF8(obs.c_str()) );

            if(category == ""){
                wxGridCellAttr *attrImultLine = new wxGridCellAttr();
                attrImultLine->SetReadOnly(true);
                gdEstimates->SetRowAttr(i, attrImultLine);
            }
            ++i;
        };
        if(lbMonths->GetSelection() > _activeIndex){
            using namespace std::placeholders;
            _estimatePlaningView.budgetId(budget_id);
            _document->look(_estimatePlaningView, std::bind(refreshFunction, _1, _2, _3, _4, 0, 0, _5, _6));
        } else {
            _estimateExecutingView.budgetId(budget_id);
            _document->look(_estimateExecutingView, refreshFunction);
        }
        RefreshCellAttr();

    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshStatusBar()
{
    int budget_id = lbMonths->GetSelection()+1;
    if(budget_id < 1){
        return;
    }
    try{
        auto query= "SELECT "
                    "    budget.name,"
                    "    SUM(estimate.amount)/100.0,"
                    "    SUM(execution_estimate.amount)/100.0,"
                    "    (SUM(execution_estimate.amount) - SUM(estimate.amount))/100.0"
                    "  FROM budget"
                    "  JOIN estimate USING(budget_id)"
                    "  LEFT JOIN (SELECT "
                    "      IFNULL(SUM(execution.amount), 0) AS amount,"
                    "      estimate_id"
                    "    FROM execution GROUP BY estimate_id"
                    "  ) execution_estimate USING(estimate_id)"
                    "  WHERE budget_id = ?1"
        ;
        SQLite::Statement stm(_document->_model, query);
        stm.bind(1, budget_id);
        if(!stm.executeStep()){
            wxMessageBox("ERROR?");
        }
        sbStatus->SetStatusText(L"Budget: " + wxString::FromUTF8(stm.getColumn(0)), 1);
        sbStatus->SetStatusText(L"Estimated: " + wxString::FromUTF8(stm.getColumn(1)), 2);
        sbStatus->SetStatusText(L"Accounted: " + wxString::FromUTF8(stm.getColumn(2)), 3);
        sbStatus->SetStatusText(L"Difference: " + wxString::FromUTF8(stm.getColumn(3)), 4);
    } catch (const std::exception &e){
        wxMessageBox(e.what());
    }
}


void OrcamentoMainFrame::RefreshCellAttr()
{
    //Category
    wxGridCellAttr *attrCategoryCol = new wxGridCellAttr();
    wxArrayString choices;
    SQLite::Statement choicesStm(_document->_model, "SELECT name FROM category ORDER BY category_id ASC");
    while(choicesStm.executeStep()){
        choices.Add(wxString::FromUTF8(choicesStm.getColumn(0)));
    }
    attrCategoryCol->SetEditor(new wxGridCellChoiceEditor(choices));
    gdEstimates->SetColAttr(EstimateColumn::CATEGORY, attrCategoryCol);

    //Show the execution only if possible.
    if(lbMonths->GetSelection() > _activeIndex){
        gdEstimates->HideCol(EstimateColumn::ACCOUNTED);
        gdEstimates->HideCol(EstimateColumn::REMAINING);
    } else {
        gdEstimates->ShowCol(EstimateColumn::ACCOUNTED);
        gdEstimates->ShowCol(EstimateColumn::REMAINING);
    }
}


void OrcamentoMainFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OrcamentoMainFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxAboutDialogInfo info;
    info.SetName(_("OrcaMento"));
    info.SetVersion(_("0.1 Alpha"));
//    info.SetVersion(_("Build ")+isoDate()+_("(")+msg+_(")"));
    info.SetDescription(_("A small program to manage finances. \n"));
    info.SetCopyright(_("(C) 2014 TalesM (talesm.github.io, tales.miranda88@gmail.com)"));
    info.SetWebSite(_("https://github.com/TalesM/orcamento"));
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("orca_1.ico"))));
        info.SetIcon(FrameIcon);

    wxString licenseString = "This program is licensed by the terms of GPL 3.\nSee the included <LICENSE.txt> for more detail.";
    info.SetLicence(licenseString);

    wxAboutBox(info);
}

void OrcamentoMainFrame::OnNew(wxCommandEvent& event)
{
    CreateDatabaseDialog dialog(this);
DIALOG_SHOW: //Don't do this at home, kids.
    if(dialog.ShowModal() != wxID_OK ){
        return;
    }
    wxString location = dialog.getLocation();
    if(location.Trim().length()==0){
        wxMessageBox("Invalid Path");
        goto DIALOG_SHOW;
    }
    wxDateTime start  = dialog.getStart();

    // Begin transaction
    wxString model;
    wxFile modelFile(L"theModel.sql");
    if(modelFile.ReadAll(&model)){
        try{
            _document = OrcaDocument::create(location, start);
        } catch (const std::exception &e){
            wxMessageBox(e.what());
            _document = nullptr;
            goto DIALOG_SHOW;
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
        if(!_document->_model.exec("INSERT INTO budget(name, start, duration) "
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
        if(!_document->_model.exec("UPDATE budget SET executing = 1"
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
    if(openFileDialog.ShowModal() != wxID_OK){
        return;
    }
    wxString location = openFileDialog.GetPath();
    try {
        _document = OrcaDocument::load(location);
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
    try {
        auto query = "INSERT INTO estimate(budget_id, amount, category_id)"
                     "  VALUES (?1, 0, (SELECT max(category_id) FROM category))";
        SQLite::Statement stm(_document->_model, query);
        stm.bind(1, selection);
        if(!stm.exec()){
            wxMessageBox("Erro desconhecido");
        }
        gdEstimates->AppendRows();
        int newRow = gdEstimates->GetNumberRows()-1;
        gdEstimates->SetCellValue(newRow, 0, wxString::FromDouble(_document->_model.getLastInsertRowid()));
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
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
            SQLite::Statement stm(_document->_model, query);
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
        updateField("name", newValue.ToUTF8());
        break;
    case EstimateColumn::ESTIMATED:
        updateField("amount", int(atof(newValue)*100));
        RefreshStatusBar();
        break;
    case EstimateColumn::DUE:
        try{
            if(newValue.length()){
                wxDateTime due{};
                due.ParseISODate(newValue);
                int day = due.GetDay() -1;
                std::string query = "UPDATE estimate SET \"due\" = ?2|| ' days' WHERE estimate_id = ?1";
                SQLite::Statement stm(_document->_model, query);
                stm.bind(1, int(id));
                stm.bind(2, day);
                if(!stm.exec()){
                    wxMessageBox("Erro desconhecido");
                }
            } else {
                std::string query = "UPDATE estimate SET \"due\" = NULL WHERE estimate_id = ?1";
                SQLite::Statement stm(_document->_model, query);
                stm.bind(1, int(id));
                if(!stm.exec()){
                    wxMessageBox("Erro desconhecido");
                }
            }
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
        break;
    case EstimateColumn::CATEGORY:
        try{
            std::string query = "UPDATE estimate SET \"category_id\" = (SELECT category_id FROM category WHERE name=?2) WHERE estimate_id = ?1";
            SQLite::Statement stm(_document->_model, query);
            stm.bind(1, int(id));
            stm.bind(2, newValue.ToUTF8());
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
    int row = event.GetRow();
    if(row < 1){
        return;
    }

    wxPoint point = event.GetPosition();
    cmnEstimate.SetClientData(reinterpret_cast<void*>(row));
    PopupMenu( &cmnEstimate, gdEstimates->GetPosition() + point);
    cmnEstimate.SetClientData(NULL);
}

void OrcamentoMainFrame::OnmnEstimateEditSelected(wxCommandEvent& event)
{
    if(cmnEstimate.GetClientData()){
        int row = reinterpret_cast<int>(cmnEstimate.GetClientData());
        ExecutionDialog executionDialog(this, wxID_ANY, atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID)));
        executionDialog.giveDatabase(_document);
        executionDialog.ShowModal();
        _document = executionDialog.takeDatabase();
        RefreshEstimates();
        RefreshStatusBar();
    }
}

void OrcamentoMainFrame::OnmnEstimateDeleteSelected(wxCommandEvent& event)
{
    if(cmnEstimate.GetClientData()){
        int row = reinterpret_cast<int>(cmnEstimate.GetClientData());
        if(wxMessageBox(L"Are you sure you want to delete \""
                        +gdEstimates->GetCellValue(row, EstimateColumn::NAME)+"\"",
                        "Delete Confirmation", wxOK|wxCENTRE|wxCANCEL, this) != wxOK
        ){
            return;
        }
        try {
            SQLite::Statement stm(_document->_model, "DELETE FROM estimate WHERE estimate_id = ?1");
            stm.bind(1, gdEstimates->GetCellValue(row, EstimateColumn::ID));
            stm.exec();
            RefreshEstimates();
            RefreshStatusBar();
        } catch(std::exception &e){
            wxMessageBox(e.what());
        }
    } else {
        wxMessageBox(L"Unknown error. Event called by wrong caller.");
    }
}

void OrcamentoMainFrame::OnWalletsOverview(wxCommandEvent& event)
{
    WalletOverviewDialog overview(this);
    overview.giveDatabase(_document);
    overview.ShowModal();
    _document = overview.takeDatabase();
}

void OrcamentoMainFrame::OngdEstimatesCellLeftDClick(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    if(row <= 0){
        return;
    }
    if(col == EstimateColumn::ACCOUNTED){
        ExecutionDialog executionDialog(this, wxID_ANY, atoi(gdEstimates->GetCellValue(row, 0)));
        executionDialog.giveDatabase(_document);
        executionDialog.ShowModal();
        _document = executionDialog.takeDatabase();
        RefreshEstimates();
        RefreshStatusBar();
    } else if(col ==EstimateColumn::OBS){
        wxTextEntryDialog obsDialog(this, L"Write an Observation for \""+gdEstimates->GetCellValue(row, EstimateColumn::NAME)+L"\"",
                                    L"OBS", gdEstimates->GetCellValue(row, EstimateColumn::OBS), wxTE_MULTILINE|wxTextEntryDialogStyle);
        if(obsDialog.ShowModal() != wxID_OK){
            return;
        }
        try{
            int id = atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID));
            SQLite::Statement stm(_document->_model, R"==(UPDATE "estimate" SET "obs" = ?2 WHERE "estimate_id" = ?1 )==");
            stm.bind(1, id);
            stm.bind(2, obsDialog.GetValue().ToUTF8());
            stm.exec();
            gdEstimates->SetCellValue(row, EstimateColumn::OBS, obsDialog.GetValue());
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    }
}


void OrcamentoMainFrame::OnmnEstimateCopySelectedToSelected(wxCommandEvent& event)
{
    wxArrayInt selectedRows = gdEstimates->GetSelectedRows();
    if(selectedRows.size()==0){
        wxMessageBox(L"You need to select at least an entire row.");
        return;
    }
    int budget_id = lbMonths->GetSelection()+1;
    if(budget_id <= 0){
        return;
    }
    int increment = 0;
    try{
        auto query ="SELECT name FROM budget WHERE budget_id > ?1 ORDER BY budget_id ASC";
        SQLite::Statement stm(_document->_model, query);
        stm.bind(1, budget_id);
        wxArrayString options;
        while(stm.executeStep()){
            options.push_back(wxString::FromUTF8(stm.getColumn(0)));
        }
        if(options.size()==0){
            wxMessageBox(L"This is the last budget.");
            return;
        }
        increment = 1 + wxGetSingleChoiceIndex(L"Select the destiny Budget", "Select Budget", options, 0, this);
    }catch (const std::exception &e){
        wxMessageBox(e.what());
    }
    if(increment <=0){
        return;
    }
    for(int row: selectedRows){
        int id = atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID));
        try{
            auto query ="INSERT OR REPLACE INTO estimate(budget_id, category_id,name, amount, due, obs)"
                        "  SELECT budget_id + ?2, category_id, name, amount, due, obs"
                        "    FROM estimate "
                        "    WHERE category_id IS NOT NULL "
                        "      AND name IS NOT NULL "
                        "      AND estimate_id = ?1";
            SQLite::Statement stm(_document->_model, query);
            stm.bind(1, id);
            stm.bind(2, increment);
//            stm.bind(2, obsDialog.GetValue());
            stm.exec();
        }catch (const std::exception &e){
            wxMessageBox(e.what());
        }
    }
}
