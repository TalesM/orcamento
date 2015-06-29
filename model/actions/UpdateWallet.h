#ifndef _ORCAACTION_UPDATEWALLET_H
#define _ORCAACTION_UPDATEWALLET_H

#include "../OrcaAction.h"

namespace action
{
class UpdateWallet : public OrcaAction
{
public:
    UpdateWallet(int walletId, const std::string &name, const std::string &obs):
        _walletId(walletId),
        _name(name),
        _obs(obs)
    {}
    virtual ~UpdateWallet() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "UPDATE wallet SET name = ?2, obs = ?3 WHERE wallet_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _walletId);
        stm.bind(2, _name  );
        stm.bind(3, _obs  );
        if(!stm.exec()) {
            throw std::runtime_error("Wallet id invalid.");
        }
    }
private:
    int _walletId;
    std::string _name;
    std::string _obs;
};
}

#endif // _ORCAACTION_UPDATEWALLET_H

