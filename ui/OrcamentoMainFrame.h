#ifndef ORCAMENTOMAINFRAME_H
#define ORCAMENTOMAINFRAME_H
#include "wxcrafter.h"

#include <memory>
#include "BudgetFilter.h"
#include "model/OrcaDocument.h"
#include "model/Search.h"
#include "model/views/BudgetToCopyView.h"
#include "model/views/BudgetView.h"
#include "model/views/CategoryView.h"
#include "model/views/EstimateExecutingView.h"
#include "model/views/EstimatePlaningView.h"
#include "model/views/TotalsView.h"

class OrcamentoMainFrame : public OrcamentoMainFrameBase
{
public:
    OrcamentoMainFrame(wxWindow* parent);
    virtual ~OrcamentoMainFrame();
private:
    std::unique_ptr<OrcaDocument> _document;
    Search _search;
    int _activeIndex = -1;
    int _sort;
    bool _asc=true;
    BudgetView _budgetView;
    CategoryView _categoryView;
    EstimateExecutingView _estimateExecutingView;
    EstimatePlaningView _estimatePlaningView;
    TotalsView _totalsView;
    BudgetToCopyView _budgetCopyView;
    BudgetFilter *dgFilter = nullptr;

    wxGridCellAttr *attrNothing;
    
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
    virtual void OnMneditredoMenuSelected(wxCommandEvent& event);
    virtual void OnMnfileundoMenuSelected(wxCommandEvent& event);
    virtual void OnGdestimatesGridColSort(wxGridEvent& event) override;
    virtual void OnByfiltertotalsButtonClicked(wxCommandEvent& event) override;
    virtual void OnLsmonthsListbox(wxCommandEvent& event) override;
    virtual void OnCmestimatescopyselectedrowsMenuSelected(wxCommandEvent& event) override;
    virtual void OnCmestimatesdeleteMenuSelected(wxCommandEvent& event) override;
    virtual void OnCmestimatesexecuteMenuSelected(wxCommandEvent& event) override;
    virtual void OnCloseWindow(wxCloseEvent& event) override;
    virtual void OnGdestimatesGridCellChanging(wxGridEvent& event) override;
    virtual void OnGdestimatesGridCellLeftDclick(wxGridEvent& event) override;
    virtual void OnGdestimatesGridCellRightClick(wxGridEvent& event) override;
    virtual void OnMnbudgetcreatenextMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnbudgetexecutenextMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnbudgetexportMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnbudgetseparatorMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnestimateaddMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnfilenewMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnfilequitMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnfilesaveMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnfilesaveasMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnhelpaboutMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnwalletoverviewMenuSelected(wxCommandEvent& event) override;
    virtual void OnMnfileopenMenuSelected(wxCommandEvent& event) override;
};
#endif // ORCAMENTOMAINFRAME_H
