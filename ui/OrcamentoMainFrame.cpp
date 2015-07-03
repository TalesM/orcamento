#include "OrcamentoMainFrame.h"
#include <string>
#include <vector>
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include "CSV.hpp"
#include "CreateDatabaseDialog.h"
#include "ExecutionDialog.h"
#include "WalletOverviewDialog.h"

#include "model/actions/CopySelectedEstimateTo.h"
#include "model/actions/DeleteEstimate.h"
#include "model/actions/InsertBudget.h"
#include "model/actions/InsertEstimate.h"
#include "model/actions/ExecuteNextBudget.h"
#include "model/actions/UpdateEstimate.h"

// helper functions
enum wxbuildinfoformat { short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    if(format == long_f) {
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

inline wxString isoDate()
{
    wxString date(__DATE__), time(__TIME__);
    wxDateTime isoDate;
    isoDate.ParseFormat(date + " " + time, "%b %d %Y %T");
    return isoDate.FormatISOCombined();
}

namespace EstimateColumn
{
constexpr int ID = 0, NAME = 1, DUE = 2, ESTIMATED = 3, ACCOUNTED = 4, REMAINING = 5, CATEGORY = 6, OBS = 7;
constexpr int length = 8;
};

OrcamentoMainFrame::OrcamentoMainFrame(wxWindow* parent)
    : OrcamentoMainFrameBase(parent)
{
    gdEstimates->AppendCols(8);
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

    SetupCellAttr();
}

OrcamentoMainFrame::~OrcamentoMainFrame()
{
}

void OrcamentoMainFrame::SetupCellAttr()
{
    // Columns
    auto moneyRenderer = new wxGridCellFloatRenderer(-1, 2);
    // Due
    wxGridCellAttr* attrDueCol = new wxGridCellAttr();
    attrDueCol->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdEstimates->SetColAttr(EstimateColumn::DUE, attrDueCol);

    // Expected
    wxGridCellAttr* attrExpectedCol = new wxGridCellAttr();
    attrExpectedCol->SetRenderer(moneyRenderer);
    attrExpectedCol->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdEstimates->SetColAttr(EstimateColumn::ESTIMATED, attrExpectedCol);

    // Accounted
    moneyRenderer->IncRef();
    wxGridCellAttr* attrAccountedCol = new wxGridCellAttr();
    attrAccountedCol->SetReadOnly(true);
    attrAccountedCol->SetRenderer(moneyRenderer);
    gdEstimates->SetColAttr(EstimateColumn::ACCOUNTED, attrAccountedCol);

    // Remaining
    moneyRenderer->IncRef();
    wxGridCellAttr* attrRemainingCol = new wxGridCellAttr();
    attrRemainingCol->SetReadOnly(true);
    attrRemainingCol->SetRenderer(moneyRenderer);
    gdEstimates->SetColAttr(EstimateColumn::REMAINING, attrRemainingCol);

    // OBS
    wxGridCellAttr* obsCol = new wxGridCellAttr();
    obsCol->SetReadOnly();
    gdEstimates->SetColAttr(EstimateColumn::OBS, obsCol);

    // ROWS
    wxColour red{ 0xAAAAFF }, green{ 0xAAFFAA }, yellow{ 0xAAD4D4 }, blue{ 0xFFAAAA }, magenta{ 0xD4AAD4 },
        orange{ 0xAAD4FF }, white{ 0xFFFFFF };

    attrNothing = new wxGridCellAttr();
    attrNothing->SetReadOnly(true);

    attrCredit = new wxGridCellAttr();
    attrCredit->SetBackgroundColour(green);

    attrDebit = new wxGridCellAttr();
    attrDebit->SetBackgroundColour(magenta);

    attrNeutral = new wxGridCellAttr();
    attrNeutral->SetBackgroundColour(yellow);

    attrCreditNone = new wxGridCellAttr();
    attrCreditNone->SetBackgroundColour(white);

    attrCreditPending = new wxGridCellAttr();
    attrCreditPending->SetBackgroundColour(orange);

    attrCreditReceived = new wxGridCellAttr();
    attrCreditReceived->SetBackgroundColour(green);

    attrDebitNone = new wxGridCellAttr();
    attrDebit->IncRef();

    attrDebitPending = new wxGridCellAttr();
    attrDebitPending->SetBackgroundColour(blue);

    attrDebitPaid = new wxGridCellAttr();
    attrDebitPaid->SetBackgroundColour(magenta);

    attrDebitOverpaid = new wxGridCellAttr();
    attrDebitOverpaid->SetBackgroundColour(red);
}

void OrcamentoMainFrame::RefreshModel()
{
    lsMonths->Clear();
    try {
        _activeIndex = -1;
        _document->look(_budgetView, [this](int id, std::string name, int executing, int active) {
            wxString budgetName(wxString::FromUTF8(name.c_str()));
            if(not executing) {
                budgetName = "<em>" + budgetName + "</em>";
            } else if(active) {
                budgetName = "<strong>" + budgetName + "</strong>";
                _activeIndex = lsMonths->GetCount();
            }
            lsMonths->Append(budgetName, reinterpret_cast<void*>(id));
            if(active) {
                lsMonths->SetSelection(lsMonths->GetCount() - 1);
                RefreshTotals();
            }
        });
        if(!lsMonths->GetSelectedCount()){
            lsMonths->SetSelection(lsMonths->GetCount()-1);
        }
        RefreshEstimates();
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshEstimates()
{
    if(gdEstimates->GetNumberRows()) {
        gdEstimates->DeleteRows(0, gdEstimates->GetNumberRows());
    }
    int budget_id = selectedBudgetId();
    if(budget_id <= 0) {
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
                                          std::string obs) {
            gdEstimates->AppendRows();
            gdEstimates->SetCellValue(i, EstimateColumn::ID, wxString::FromDouble(id));
            gdEstimates->SetCellValue(i, EstimateColumn::NAME, wxString::FromUTF8(name.c_str()));
            gdEstimates->SetCellValue(i, EstimateColumn::DUE, wxString::FromUTF8(due.c_str()));
            gdEstimates->SetCellValue(i, EstimateColumn::ESTIMATED, wxString::FromDouble(estimated));
            gdEstimates->SetCellValue(i, EstimateColumn::ACCOUNTED, wxString::FromDouble(accounted));
            gdEstimates->SetCellValue(i, EstimateColumn::REMAINING, wxString::FromDouble(remaining));
            gdEstimates->SetCellValue(i, EstimateColumn::CATEGORY, wxString::FromUTF8(category.c_str()));
            gdEstimates->SetCellValue(i, EstimateColumn::OBS, wxString::FromUTF8(obs.c_str()));

            if(category == "") {
                attrNothing->IncRef();
                gdEstimates->SetRowAttr(i, attrNothing);
            } else {
                RefreshColorEstimate(i, estimated, accounted);
            }
            ++i;
        };
        if(lsMonths->GetSelection() > _activeIndex) {
            using namespace std::placeholders;
            _estimatePlaningView.budgetId(budget_id);
            _document->look(_estimatePlaningView, std::bind(refreshFunction, _1, _2, _3, _4, 0, 0, _5, _6));
            RefreshCellAttr(false);
        } else {
            _estimateExecutingView.budgetId(budget_id);
            _document->look(_estimateExecutingView, refreshFunction);
            RefreshCellAttr(true);
        }

    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshColorEstimate(int i, double estimated, double accounted)
{
    if(estimated > 0) {
        attrCredit->IncRef();
        gdEstimates->SetAttr(i, EstimateColumn::ESTIMATED, attrCredit);
        if(accounted >= estimated) {
            attrCreditReceived->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrCreditReceived);
        } else if(accounted > 0) {
            attrCreditPending->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrCreditPending);
        } else {
            attrCreditNone->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrCreditNone);
        }
    } else if(estimated < 0) {
        attrDebit->IncRef();
        gdEstimates->SetAttr(i, EstimateColumn::ESTIMATED, attrDebit);
        if(accounted < estimated) {
            attrDebitOverpaid->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrDebitOverpaid);
        } else if(accounted == estimated) {
            attrDebitPaid->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrDebitPaid);
        } else if(accounted < 0) {
            attrDebitPending->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrDebitPending);
        } else {
            attrDebitNone->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrDebitNone);
        }
    } else {
        attrNeutral->IncRef();
        gdEstimates->SetAttr(i, EstimateColumn::ESTIMATED, attrNeutral);
        if(accounted > 0) {
            attrCredit->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrCredit);
        } else {
            attrDebit->IncRef();
            gdEstimates->SetAttr(i, EstimateColumn::ACCOUNTED, attrDebit);
        }
    }
}

void OrcamentoMainFrame::RefreshTotals()
{
    int budget_id = selectedBudgetId();
    if(budget_id < 1) {
        return;
    }
    try {
        _totalsView.budgetId(budget_id);
        if(_search){
            _totalsView.search(_search);
        }
        bool ok = false;
        _document->look(_totalsView,
                        [this, &ok](const std::string& budget, double estimated, double accounted, double remaining) {
//            sbStatus->SetStatusText(_("Budget: ") + wxString::FromUTF8(budget.c_str()), 1);
            txTotalEstimated->SetValue( wxString::FromDouble(estimated, 2));
            txTotalAccounted->SetValue(wxString::FromDouble(accounted, 2));
            txTotalRemaining->SetValue(wxString::FromDouble(remaining, 2));
            ok = true;
        });
        if(!ok) {
            wxMessageBox("Database inconsitence. Do you have a backup?");
        }
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}

void OrcamentoMainFrame::RefreshCellAttr(bool executing)
{
    // Category
    wxGridCellAttr* attrCategoryCol = new wxGridCellAttr();
    wxArrayString choices;
    _document->look(_categoryView,
                    [this, &choices](const std::string& name) { choices.Add(wxString::FromUTF8(name.c_str())); });
    attrCategoryCol->SetEditor(new wxGridCellChoiceEditor(choices));
    gdEstimates->SetColAttr(EstimateColumn::CATEGORY, attrCategoryCol);

    // Show the execution only if possible.
    if(executing) {
        gdEstimates->ShowCol(EstimateColumn::ACCOUNTED);
        gdEstimates->ShowCol(EstimateColumn::REMAINING);
    } else {
        gdEstimates->HideCol(EstimateColumn::ACCOUNTED);
        gdEstimates->HideCol(EstimateColumn::REMAINING);
    }
}
void OrcamentoMainFrame::OnMnbudgetcreatenextMenuSelected(wxCommandEvent& event)
{
    if(wxMessageBox(L"Are you sure you want to create a new Budget?", L"Create Budget", wxYES_NO|wxCENTRE) != wxYES) {
        return;
    }
    try {
        _document->exec<action::InsertBudget>();
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
    RefreshModel();
}
void OrcamentoMainFrame::OnMnbudgetexecutenextMenuSelected(wxCommandEvent& event)
{
    if(wxMessageBox(L"Are you sure you want to execute the next Budget?", L"Execute Budget", wxYES_NO|wxCENTRE) != wxYES) {
        return;
    }
    try {
        _document->exec<action::ExecuteNextBudget>();
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
    RefreshModel();
}
void OrcamentoMainFrame::OnMnbudgetexportMenuSelected(wxCommandEvent& event)
{
    int budget_id = selectedBudgetId();
    if(budget_id <= 0) {
        return;
    }
    wxFileDialog openFileDialog(this, L"Select the location to export", "", "", "CSV(*.csv)|*.csv", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(openFileDialog.ShowModal() != wxID_OK) {
        return;
    }
    wxString location = openFileDialog.GetPath();

    using namespace jay::util;
    CSVwrite writter(location.ToStdString());
    writter.WriteUTF8BOM();
    writter.WriteRecord({"id", "name", "estimated", "accounted", "remaining", "category", "Obs"});
    for(int i=0; i < gdEstimates->GetRows();++i){
        writter.WriteRecord({
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::ID).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::NAME).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::DUE).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::ESTIMATED).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::ACCOUNTED).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::CATEGORY).ToUTF8(),
            (std::string)gdEstimates->GetCellValue(i, EstimateColumn::OBS).ToUTF8(),
        });
    }
}
void OrcamentoMainFrame::OnMnbudgetseparatorMenuSelected(wxCommandEvent& event)
{
}
void OrcamentoMainFrame::OnMnestimateaddMenuSelected(wxCommandEvent& event)
{
    int selection = selectedBudgetId();
    if(!selection) {
        return;
    }
    try {
        int newEstimate = _document->exec<action::InsertEstimate>(selection);
        gdEstimates->AppendRows();
        int newRow = gdEstimates->GetNumberRows()-1;
        gdEstimates->SetCellValue(newRow, 0, wxString::FromDouble(newEstimate));
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
void OrcamentoMainFrame::OnMnfilenewMenuSelected(wxCommandEvent& event)
{
    CreateDatabaseDialog dialog(this);
DIALOG_SHOW: //Don't do this at home, kids.
    if(dialog.ShowModal() != wxID_OK ) {
        return;
    }
    wxString location = dialog.getLocation();
    if(location.Trim().length()==0) {
        wxMessageBox("Invalid Path");
        goto DIALOG_SHOW;
    }
    wxDateTime start  = dialog.getStart();

    try {
        _document = OrcaDocument::create(location, start);
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
        _document = nullptr;
        goto DIALOG_SHOW;
    }
    RefreshModel();
}

void OrcamentoMainFrame::OnMnfileopenMenuSelected(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(
        this, L"Select the file", "", "", "Orca files (*.orca)|*.orca", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(openFileDialog.ShowModal() != wxID_OK) {
        return;
    }
    wxString location = openFileDialog.GetPath();
    try {
        _document = OrcaDocument::load(location);
        RefreshModel();
    } catch(const wrongver_error& e) {
        if(OrcaDocument::canConvert(e.major, e.minor, e.patch, e.variant)) {
            try {
                wxString backupLocation = location + ".old";
                if(rename(location, backupLocation)!=0){
                    std::runtime_error("Can not backup.");
                }
                _document = OrcaDocument::convert(backupLocation, location);
                RefreshModel();
            } catch(const std::exception& e) {
                wxMessageBox(e.what());
            }
        } else {
            wxMessageBox(e.what());
        }
    } catch(const std::exception& e) {
        wxMessageBox(e.what());
    }
}
void OrcamentoMainFrame::OnMnfilequitMenuSelected(wxCommandEvent& event)
{
    Close();
}
void OrcamentoMainFrame::OnMnfilesaveMenuSelected(wxCommandEvent& event)
{
    _document->save();
}
void OrcamentoMainFrame::OnMnfilesaveasMenuSelected(wxCommandEvent& event)
{
}
void OrcamentoMainFrame::OnMnhelpaboutMenuSelected(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxAboutDialogInfo info;
    info.SetName(_("OrcaMento"));
//    info.SetVersion(_("0.3 Alpha"));
    info.SetVersion(_("Build ")+isoDate()+_("(")+msg+_(")"));
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
void OrcamentoMainFrame::OnMnwalletoverviewMenuSelected(wxCommandEvent& event)
{
    WalletOverviewDialog overview(this);
    overview.giveDatabase(_document);
    overview.ShowModal();
    _document = overview.takeDatabase();
}
void OrcamentoMainFrame::OnCloseWindow(wxCloseEvent& event)
{
    if(!event.CanVeto() || !_document || !_document->dirt()) {
        Destroy();
    } else  {
        auto ans = wxMessageBox(_("Do you want to save your budget before exit?"),
                                _("OrcaMento"), wxYES_NO | wxCANCEL | wxCENTRE, this);
        switch(ans) {
        case wxYES:
            _document->save();
            Destroy();
            break;
        case wxNO:
            Destroy();
            break;
        case wxCANCEL:
            break;
        }
    }
}
void OrcamentoMainFrame::OnGdestimatesGridCellChanging(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    wxString newValue = event.GetString();
    if(event.GetString() == gdEstimates->GetCellValue(row, col)) { //The default editor duplicate events, so this avoids the first one.
        return;
    }
    long id;
    if(!gdEstimates->GetCellValue(row, EstimateColumn::ID).ToCLong(&id)) {
        wxMessageBox(L"Corrupted Row: '"+gdEstimates->GetColLabelValue(0)+"'");
        return;
    }
    int estimateId = int(id);
    try {
        switch(col) {
        case EstimateColumn::NAME:
            _document->exec<action::UpdateEstimateName>(estimateId, std::string(newValue.ToUTF8()));
            break;
        case EstimateColumn::ESTIMATED:{
            double newEstimated = atof(newValue);
            _document->exec<action::UpdateEstimateAmount>(estimateId, newEstimated);
            RefreshTotals();
            RefreshColorEstimate(row, newEstimated, atof(gdEstimates->GetCellValue(row, EstimateColumn::ACCOUNTED)));
            break;
        }
        case EstimateColumn::DUE:
            if(newValue.length()) {
                wxDateTime due{};
                due.ParseISODate(newValue);
                int day = due.GetDay() -1;
                _document->exec<action::UpdateEstimateDue>(estimateId, day);
            } else {
                _document->exec<action::DeleteEstimateDue>(estimateId);
            }
            break;
        case EstimateColumn::CATEGORY:
            _document->exec<action::UpdateEstimateCategory>(estimateId, std::string(newValue.ToUTF8()));
            break;
        default:
            break;
        }
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
void OrcamentoMainFrame::OnGdestimatesGridCellLeftDclick(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    if(col == EstimateColumn::ACCOUNTED) {
        ExecutionDialog executionDialog(this, wxID_ANY, atoi(gdEstimates->GetCellValue(row, 0)));
        executionDialog.giveDatabase(_document);
        executionDialog.ShowModal();
        _document = executionDialog.takeDatabase();
        RefreshEstimates();
        RefreshTotals();
    } else if(col ==EstimateColumn::OBS) {
        wxTextEntryDialog obsDialog(this, L"Write an Observation for \""+gdEstimates->GetCellValue(row, EstimateColumn::NAME)+L"\"",
                                    L"OBS", gdEstimates->GetCellValue(row, EstimateColumn::OBS), wxTE_MULTILINE|wxTextEntryDialogStyle);
        if(obsDialog.ShowModal() != wxID_OK) {
            return;
        }
        try {
            int id = atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID));
            auto val = obsDialog.GetValue();
            _document->exec<action::UpdateEstimateObs>(id, std::string(val.ToUTF8()));
            gdEstimates->SetCellValue(row, EstimateColumn::OBS, val);
        } catch (const std::exception &e) {
            wxMessageBox(e.what());
        }
    }
}
void OrcamentoMainFrame::OnGdestimatesGridCellRightClick(wxGridEvent& event)
{
    int row = event.GetRow();
    wxPoint point = event.GetPosition();
    cmEstimate->SetClientData(reinterpret_cast<void*>(row));
    PopupMenu( cmEstimate, gdEstimates->GetPosition() + point);
    cmEstimate->SetClientData(NULL);
}
 
void OrcamentoMainFrame::OnCmestimatescopyselectedrowsMenuSelected(wxCommandEvent& event)
{
    wxArrayInt selectedRows = gdEstimates->GetSelectedRows();
    if(selectedRows.size()==0) {
        wxMessageBox(L"You need to select at least an entire row.");
        return;
    }
    int budget_id = lsMonths->GetSelection()+1;
    if(budget_id <= 0) {
        return;
    }
    int increment = 0;
    try {
        _budgetCopyView.sourceBudgetId(budget_id);
        wxArrayString options;
        bool ok = false;
        _document->look(_budgetCopyView, [this, &options, &ok](const std::string &name) {
            options.push_back(wxString::FromUTF8(name.c_str()));
            ok = true;
        });
        if(!ok) {
            wxMessageBox(L"This is the last budget.");
            return;
        }
        increment = 1 + wxGetSingleChoiceIndex(L"Select the destiny Budget", "Select Budget", options, 0, this);
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
    if(increment <=0) {
        return;
    }
    for(int row: selectedRows) {
        int id = atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID));
        try {
            _document->exec<action::CopySelectedEstimateTo>(id, increment);
        } catch (const std::exception &e) {
            // TODO (Tales#1#): Choose to continue or cancel.
            wxMessageBox(e.what());
        }
    }
}
void OrcamentoMainFrame::OnCmestimatesdeleteMenuSelected(wxCommandEvent& event)
{
    int row = reinterpret_cast<int>(cmEstimate->GetClientData());
    if(wxMessageBox(L"Are you sure you want to delete \""
                    +gdEstimates->GetCellValue(row, EstimateColumn::NAME)+"\"",
                    "Delete Confirmation", wxOK|wxCENTRE|wxCANCEL, this) != wxOK
      ) {
        return;
    }
    try {
        int estimateId = atoi(gdEstimates->GetCellValue(row, EstimateColumn::ID));
        _document->exec<action::DeleteEstimate>(estimateId);
        RefreshEstimates();
        RefreshTotals();
    } catch(std::exception &e) {
        wxMessageBox(e.what());
    }
}
void OrcamentoMainFrame::OnCmestimatesexecuteMenuSelected(wxCommandEvent& event)
{
    int row = reinterpret_cast<int>(cmEstimate->GetClientData());
    ExecutionDialog executionDialog(this, wxID_ANY, atoi(gdEstimates->GetCellValue(row, 0)));
    executionDialog.giveDatabase(_document);
    executionDialog.ShowModal();
    _document = executionDialog.takeDatabase();
    RefreshEstimates();
    RefreshTotals();
}
void OrcamentoMainFrame::OnLsmonthsListbox(wxCommandEvent& event)
{
    RefreshEstimates();
    RefreshTotals();
}
void OrcamentoMainFrame::OnByfiltertotalsButtonClicked(wxCommandEvent& event)
{
    if(!dgFilter){
        dgFilter = new BudgetFilter(this);
        dgFilter->addSearchListerner([this](const Search &s){
            _search = s;
            RefreshTotals();
        });
    }
    dgFilter->Show();
}
