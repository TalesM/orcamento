#ifndef ORCAMENTOMAINFRAME_H
#define ORCAMENTOMAINFRAME_H
#include "wxcrafter.h"

#include <memory>
#include "BudgetFilter.h"
#include "BudgetToCopyView.h"
#include "BudgetView.h"
#include "CategoryView.h"
#include "EstimateExecutingView.h"
#include "EstimatePlaningView.h"
#include "TotalsView.h"
#include "OrcaDocument.h"

class OrcamentoMainFrame : public OrcamentoMainFrameBase
{
public:
    OrcamentoMainFrame(wxWindow* parent);
    virtual ~OrcamentoMainFrame();
private:
    std::unique_ptr<OrcaDocument> _document;
    int _activeIndex = -1;
    BudgetView _budgetView;
    CategoryView _categoryView;
    EstimateExecutingView _estimateExecutingView;
    EstimatePlaningView _estimatePlaningView;
    TotalsView _totalsView;
    BudgetToCopyView _budgetCopyView;
    BudgetFilter *dgFilter = nullptr;

    wxGridCellAttr *attrNothing;
    ///Attribs for estimates
    wxGridCellAttr *attrCredit;
    wxGridCellAttr *attrDebit;
    wxGridCellAttr *attrNeutral;

    ///Attribs for execution
    wxGridCellAttr *attrCreditNone;
    wxGridCellAttr *attrCreditPending;
    wxGridCellAttr *attrCreditReceived;
    wxGridCellAttr *attrDebitNone;
    wxGridCellAttr *attrDebitPending;
    wxGridCellAttr *attrDebitPaid;
    wxGridCellAttr *attrDebitOverpaid;
    
    void SetupCellAttr();
    void RefreshModel();
    void RefreshEstimates();
    void RefreshCellAttr(bool executing = false);
    void RefreshTotals();
    void RefreshColorEstimate(int row, double estimated, double accounted);
    int selectedBudgetId() const
    {
        return reinterpret_cast<int>(lsMonths->GetClientData(lsMonths->GetSelection()));
    }
protected:
    virtual void OnByfiltertotalsButtonClicked(wxCommandEvent& event);
    virtual void OnLsmonthsListbox(wxCommandEvent& event);
    virtual void OnCmestimatescopyselectedrowsMenuSelected(wxCommandEvent& event);
    virtual void OnCmestimatesdeleteMenuSelected(wxCommandEvent& event);
    virtual void OnCmestimatesexecuteMenuSelected(wxCommandEvent& event);
    virtual void OnCloseWindow(wxCloseEvent& event);
    virtual void OnGdestimatesGridCellChanging(wxGridEvent& event);
    virtual void OnGdestimatesGridCellLeftDclick(wxGridEvent& event);
    virtual void OnGdestimatesGridCellRightClick(wxGridEvent& event);
    virtual void OnMnbudgetcreatenextMenuSelected(wxCommandEvent& event);
    virtual void OnMnbudgetexecutenextMenuSelected(wxCommandEvent& event);
    virtual void OnMnbudgetexportMenuSelected(wxCommandEvent& event);
    virtual void OnMnbudgetseparatorMenuSelected(wxCommandEvent& event);
    virtual void OnMnestimateaddMenuSelected(wxCommandEvent& event);
    virtual void OnMnfilenewMenuSelected(wxCommandEvent& event);
    virtual void OnMnfilequitMenuSelected(wxCommandEvent& event);
    virtual void OnMnfilesaveMenuSelected(wxCommandEvent& event);
    virtual void OnMnfilesaveasMenuSelected(wxCommandEvent& event);
    virtual void OnMnhelpaboutMenuSelected(wxCommandEvent& event);
    virtual void OnMnwalletoverviewMenuSelected(wxCommandEvent& event);
    virtual void OnMnfileopenMenuSelected(wxCommandEvent& event);
};
#endif // ORCAMENTOMAINFRAME_H
