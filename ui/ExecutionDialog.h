#ifndef EXECUTIONDIALOG_H
#define EXECUTIONDIALOG_H
#include "wxcrafter.h"
#include <model/OrcaDocument.h>
#include <memory>
#include "model/views/ExecutionSummaryView.h"
#include "model/views/ExecutionView.h"
#include "model/views/WalletView.h"


class ExecutionDialog : public ExecutionDialogBase
{
public:
    ExecutionDialog(wxWindow* parent,wxWindowID id=wxID_ANY, int estimateId =0, const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~ExecutionDialog();
    
    

    void giveDatabase(std::unique_ptr<OrcaDocument> &document);

    std::unique_ptr<OrcaDocument> takeDatabase(){
        return std::move(_document);
    }
private:
    int _estimateId;
    std::unique_ptr<OrcaDocument> _document;
    ExecutionSummaryView _executionSummaryView;
    ExecutionView _executionView;
    WalletView _walletView;

    void RefreshModel();
    void RefreshExecutions();
    void RefreshCellAttr();
protected:
    virtual void OnbtDeleteClick(wxCommandEvent& event);
    virtual void OngdExecutionsCellChange(wxGridEvent& event);
    virtual void OnbtAddClick(wxCommandEvent& event);
};
#endif // EXECUTIONDIALOG_H
