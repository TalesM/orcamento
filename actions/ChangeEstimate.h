#ifndef _ORCAACTION_CHANGEESTIMATE_H
#define _ORCAACTION_CHANGEESTIMATE_H

#include <SQLiteCpp/Statement.h>
#include <string>
#include <sstream>
#include "../OrcaAction.h"

namespace action
{

template <typename VAL>
class ChangeEstimateBase: public OrcaAction
{
public:
    ChangeEstimateBase(int estimateId, const VAL &v):
        _estimateId(estimateId),
        _value(v) {}

protected:
    void doAction(SQLite::Database &database, const std::string &field) const
    {
        auto query = "UPDATE estimate SET \""+field+"\" = ?2 WHERE estimate_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId  );
        stm.bind(2, _value);
        if(!stm.exec()) {
            throw std::runtime_error("Invalid estimate or field name.");
        }
    }
private:
    int _estimateId;
    VAL _value;
};

typedef ChangeEstimateBase<std::string> ChangeEstimateString;

/**
 * @brief Changes the name.
 */
class ChangeEstimateName: public ChangeEstimateString
{
public:
    ChangeEstimateName(int estimateId, const std::string &v): ChangeEstimateString(estimateId, v) {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        ChangeEstimateString::doAction(database, "name");
    }
};

/**
 * @brief Changes the amount.
 */
class ChangeEstimateAmount: public ChangeEstimateBase<int>
{
public:
    ChangeEstimateAmount(int estimateId, double v): ChangeEstimateBase<int>(estimateId, round(v*100)) {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        ChangeEstimateBase<int>::doAction(database, "amount");
    }
};

/**
 * @brief Changes the due.
 */
class ChangeEstimateDue: public ChangeEstimateString
{
public:
    ChangeEstimateDue(int estimateId, int v): ChangeEstimateString(estimateId, to_string(v)) {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        ChangeEstimateString::doAction(database, "name");
    }

    static std::string to_string(int v)
    {
        std::stringstream ss;
        ss << v << " days";
        return ss.str();
    }
};

/**
 * Remove due to null
 */
class RemoveEstimateDue : public OrcaAction
{
public:
    RemoveEstimateDue(int estimateId):_estimateId(estimateId) {}
    virtual ~RemoveEstimateDue() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "UPDATE estimate SET \"due\" = NULL WHERE estimate_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId  );
        if(!stm.exec()) {
            throw std::runtime_error("Invalid estimate");
        }
    }
private:
    int _estimateId;
};

/**
 * Change category to null
 */
class ChangeEstimateCategory : public OrcaAction
{
public:
    ChangeEstimateCategory(int estimateId, const std::string &name):
        _estimateId(estimateId),
        _name(name)
    {}
    virtual ~ChangeEstimateCategory() {}
protected:
    virtual void doAction(SQLite::Database &database) const override
    {
        auto query = "UPDATE estimate SET \"category_id\" = (SELECT category_id FROM category WHERE name=?2) WHERE estimate_id = ?1";
        SQLite::Statement stm(database, query);
        stm.bind(1, _estimateId  );
        stm.bind(2, _name  );
        if(!stm.exec()) {
            throw std::runtime_error("Invalid estimate");
        }
    }
private:
    int _estimateId;
    std::string _name;
};

}

#endif // _ORCAACTION_CHANGEESTIMATE_H

