#ifndef _ORCA_WALLETDETAILVIEW_H
#define _ORCA_WALLETDETAILVIEW_H

#include "../OrcaView.h"


class WalletDetailView : public OrcaView<std::string, std::string, int>
{
public:
    WalletDetailView();
    virtual ~WalletDetailView();

    int walletId() const
    {
        return _walletId;
    }

    void walletId(int value)
    {
        _walletId = value;
    }
private:
    int _walletId;

    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_WALLETDETAILVIEW_H
