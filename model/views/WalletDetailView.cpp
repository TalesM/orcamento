#include "WalletDetailView.h"

static auto sql = R"=(
SELECT name, wallet.obs, COUNT(execution_id)
    FROM wallet LEFT JOIN execution USING(wallet_id)
    WHERE wallet_id = ?1
)=";

WalletDetailView::WalletDetailView():
    OrcaView(sql)
{
    //ctor
}

WalletDetailView::~WalletDetailView()
{
    //dtor
}

void WalletDetailView::setup(SQLite::Statement& stm)
{
    stm.bind(1, _walletId);
}

