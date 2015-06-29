#ifndef _ORCAACTION_INSERTWALLET_H
#define _ORCAACTION_INSERTWALLET_H

#include "../OrcaAction.h"

namespace action
{
class InsertWallet : public OrcaAction
{
public:
    InsertWallet(const std::string &name, const std::string &obs):
        _name(name),
        _obs(obs)
    {}
    virtual ~InsertWallet() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "INSERT INTO wallet(name, obs) VALUES (?2, ?3)";
        SQLite::Statement stm(database, query);
        stm.bind(2, _name  );
        stm.bind(3, _obs  );
        if(!stm.exec()) {
            throw std::runtime_error("Unknown error");
        }
    }
private:
    std::string _name;
    std::string _obs;
};
}

#endif // _ORCAACTION_INSERTWALLET_H
