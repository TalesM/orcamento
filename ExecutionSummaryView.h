#ifndef _ORCA_EXECUTIONSUMMARYVIEW_H
#define _ORCA_EXECUTIONSUMMARYVIEW_H

#include "OrcaView.h"

class ExecutionSummaryView : public OrcaView<
    std::string,    // budgetName
    std::string,    // estimateName
    double,         // estimated
    double,         // accounted
    double,         // remaining
    int             // count
    >
{
public:
    ExecutionSummaryView();
    virtual ~ExecutionSummaryView(){}
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

#endif // _ORCA_EXECUTIONSUMMARYVIEW_H
