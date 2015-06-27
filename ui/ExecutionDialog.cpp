#include "ExecutionDialog.h"
#include <vector>
#include "actions/DeleteExecution.h"
#include "actions/InsertExecution.h"
#include "actions/UpdateExecution.h"

namespace ExecutionColumn
{
constexpr int
ID          = 0,
AMOUNT      = 1,
DATE        = 2,
WALLET      = 3,
DESCRIPTION = 4,
OBS         = 5;
constexpr int length = 6;
};

ExecutionDialog::ExecutionDialog(wxWindow* parent,wxWindowID id, int estimateId,const wxPoint& pos,const wxSize& size):
    ExecutionDialogBase(parent, id), _estimateId(estimateId)
{
    gdExecutions->AppendCols(6);
    gdExecutions->SetColLabelValue(0, _("Id"));
    gdExecutions->SetColLabelValue(1, _("Amount"));
    gdExecutions->SetColLabelValue(2, _("Date"));
    gdExecutions->SetColLabelValue(3, _("Wallet"));
    gdExecutions->SetColLabelValue(4, _("Description"));
    gdExecutions->SetColLabelValue(5, _("Obs."));
    gdExecutions->HideCol(0);
}

ExecutionDialog::~ExecutionDialog()
{
}


void ExecutionDialog::giveDatabase(std::unique_ptr<OrcaDocument>& database)
{
    _document = std::move(database);
    RefreshModel();
}

void ExecutionDialog::RefreshModel()
{
    try {
        _executionSummaryView.estimateId(_estimateId);
        bool done = false;
        _document->look(_executionSummaryView, [this, &done](const std::string &budgetName,
                        const std::string &estimateName,
                        double estimated, double accounted,
        double remaining, int count) {
            assert(!done);
            done = true;
            txBudget->SetValue(wxString::FromUTF8(budgetName.c_str()));
            txEstimateName->SetValue(wxString::FromUTF8(estimateName.c_str()));
            txEstimateAmount->SetValue(wxString::FromDouble(estimated, 2));
            txAccounted->SetValue(wxString::FromDouble(accounted, 2));
            txLeftover->SetValue(wxString::FromDouble(remaining, 2));
            if(count > 0) {
                RefreshExecutions();
            }
        });
        if(!done) {
            wxMessageBox("Database possibly corrupted, do you have a backup?");
        }
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
void ExecutionDialog::RefreshExecutions()
{
    if(gdExecutions->GetNumberRows()) {
        gdExecutions->DeleteRows(0, gdExecutions->GetNumberRows());
    }
    try {
        _executionView.estimateId(_estimateId);
        int i = 0;
        _document->look(_executionView, [this, &i](int id, double amount,
                        const std::string &date,
                        const std::string &wallet,
                        const std::string &description,
        const std::string &obs) {
            gdExecutions->AppendRows();
            gdExecutions->SetCellValue(i, ExecutionColumn::ID,          wxString::FromDouble(id) );
            gdExecutions->SetCellValue(i, ExecutionColumn::AMOUNT,      wxString::FromDouble(amount, 2) );
            gdExecutions->SetCellValue(i, ExecutionColumn::DATE,        wxString::FromUTF8(date.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::WALLET,      wxString::FromUTF8(wallet.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::DESCRIPTION, wxString::FromUTF8(description.c_str()) );
            gdExecutions->SetCellValue(i, ExecutionColumn::OBS,         wxString::FromUTF8(obs.c_str()) );
            ++i;
        });
        RefreshCellAttr();
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}

void ExecutionDialog::RefreshCellAttr()
{
    wxGridCellAttr *attrReadOnly = new wxGridCellAttr();
    attrReadOnly->SetReadOnly();
    gdExecutions->SetColAttr(ExecutionColumn::ID, attrReadOnly);

    wxGridCellAttr *attrAmount = new wxGridCellAttr();
    attrAmount->SetRenderer(new wxGridCellFloatRenderer(-1, 2));
    attrAmount->SetEditor(new wxGridCellFloatEditor(-1, 2));
    gdExecutions->SetColAttr(ExecutionColumn::AMOUNT, attrAmount);

    wxGridCellAttr *attrDate = new wxGridCellAttr();
    attrDate->SetRenderer(new wxGridCellDateTimeRenderer("%B %d, %Y", "%Y-%m-%d"));
    gdExecutions->SetColAttr(ExecutionColumn::DATE, attrDate);

    attrReadOnly->IncRef();
    gdExecutions->SetColAttr(ExecutionColumn::WALLET, attrReadOnly);
}
void ExecutionDialog::OnbtAddClick(wxCommandEvent& event)
{
    std::vector<int> walletIds;
    wxArrayString walletNames;
    try {
        _document->look(_walletView, [&walletIds, &walletNames](int id, const std::string &name) {
            walletIds.push_back(id);
            walletNames.push_back(wxString::FromUTF8(name.c_str()));
        });
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
    int selected = wxGetSingleChoiceIndex(L"Choose the wallet to pay/receive money", L"Choose Wallet", walletNames);
    if(selected < 0) {
        return;
    }
    try {
        _document->exec<action::InsertExecution>(_estimateId, walletIds[selected]);
        RefreshExecutions();
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
void ExecutionDialog::OnbtDeleteClick(wxCommandEvent& event)
{
    wxArrayInt arrSelected = gdExecutions->GetSelectedRows();
    if(arrSelected.size() == 0) {
        wxMessageBox("You need to select a row to delete");
        return;
    }
    if(wxMessageBox(L"Are you sure you want do delete these executions?", "Confirm Delete", wxOK | wxCENTRE | wxCANCEL | wxICON_QUESTION, this) != wxOK) {
        return;
    }
    try {
        for(int row: arrSelected) {
            int id = atoi(gdExecutions->GetCellValue(row, ExecutionColumn::ID));
            _document->exec<action::DeleteExecution>(id);
        }
        RefreshExecutions();
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
void ExecutionDialog::OngdExecutionsCellChange(wxGridEvent& event)
{
    int row = event.GetRow(), col = event.GetCol();
    wxString newValue = event.GetString();
    if(event.GetString() == gdExecutions->GetCellValue(row, col)) { //The default editor duplicate events, so this avoids the first one.
        return;
    }
    long id;
    if(!gdExecutions->GetCellValue(row, ExecutionColumn::ID).ToCLong(&id)) {
        wxMessageBox(L"Corrupted Line: #"+gdExecutions->GetRowLabelValue(row));
        return;
    }
    int executionId = int(id);
    try {
        switch(col) {
        case ExecutionColumn::AMOUNT:
            _document->exec<action::UpdateExecutionAmount>(executionId, atof(newValue));
            RefreshModel();
            break;
        case ExecutionColumn::DATE:
            _document->exec<action::UpdateExecutionDate>(executionId, std::string(newValue.ToUTF8()));
            break;
        case ExecutionColumn::DESCRIPTION:
            _document->exec<action::UpdateExecutionDescription>(executionId, std::string(newValue.ToUTF8()));
            break;
        case ExecutionColumn::OBS:
            _document->exec<action::UpdateExecutionObs>(executionId, std::string(newValue.ToUTF8()));
            break;
        default:
            break;
        }
    } catch (const std::exception &e) {
        wxMessageBox(e.what());
    }
}
