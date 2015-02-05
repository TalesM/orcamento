#include "WalletView.h"

static auto sql = "SELECT wallet_id, name FROM wallet ORDER BY wallet_id";

WalletView::WalletView():
    OrcaView(sql)
{
    //ctor
}

WalletView::~WalletView()
{
    //dtor
}
