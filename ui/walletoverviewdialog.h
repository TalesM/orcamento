#ifndef WALLETOVERVIEWDIALOG_H
#define WALLETOVERVIEWDIALOG_H
#include <memory>
#include "wxcrafter.h"
#include "model/OrcaDocument.h"
#include "model/views/WalletView.h"
#include "model/views/WalletDetailView.h"

class WalletOverviewDialog : public WalletOverviewDialogBase
{
public:
    WalletOverviewDialog(wxWindow* parent);
    virtual ~WalletOverviewDialog();

    void giveDatabase(std::unique_ptr<OrcaDocument>& database);

    std::unique_ptr<OrcaDocument> takeDatabase()
    {
        return std::move(_document);
    }

private:
    std::unique_ptr<OrcaDocument> _document;
    WalletView _walletView;
    WalletDetailView _walletDetailView;
protected:
    virtual void OnBtokButtonClicked(wxCommandEvent& event);
    virtual void OnBtaddButtonClicked(wxCommandEvent& event);
    virtual void OnBteditButtonClicked(wxCommandEvent& event);
    virtual void OnBtremoveButtonClicked(wxCommandEvent& event);
    virtual void OnTxnameTextUpdated(wxCommandEvent& event);
    virtual void OnTxobsTextUpdated(wxCommandEvent& event);
    virtual void OnLswalletsListbox(wxCommandEvent& event);
};
#endif // WALLETOVERVIEWDIALOG_H
