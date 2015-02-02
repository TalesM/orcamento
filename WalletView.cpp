#include "WalletView.h"

static auto sql = "SELECT name FROM wallet ORDER BY wallet_id";

WalletView::WalletView():
    OrcaView(sql)
{
    //ctor
}

WalletView::~WalletView()
{
    //dtor
}
