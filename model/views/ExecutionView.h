#ifndef _ORCA_EXECUTIONVIEW_H
#define _ORCA_EXECUTIONVIEW_H

#include "../OrcaView.h"


class ExecutionView : public OrcaView<
    int,            //id
    double,         //amount
    std::string,    //date
    std::string,    //wallet
    std::string,    //description
    std::string     //obs
    >
{
public:
    ExecutionView();
    virtual ~ExecutionView(){}

    int estimateId() const
    {
        return _estimateId;
    }

    void estimateId(int value)
    {
        _estimateId = value;
    }
private:
    int _estimateId;

    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_EXECUTIONVIEW_H
