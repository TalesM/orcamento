#ifndef _ORCA_WALLETVIEW_H
#define _ORCA_WALLETVIEW_H

#include <OrcaView.h>


class WalletView : public OrcaView<std::string>
{
public:
    WalletView();
    virtual ~WalletView();
};

#endif // _ORCA_WALLETVIEW_H
