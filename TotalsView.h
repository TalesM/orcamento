#ifndef _ORCA_TOTALSVIEW_H
#define _ORCA_TOTALSVIEW_H

#include "OrcaView.h"


class TotalsView : public OrcaView<
    std::string,//Budget Name
    double,     //estimated
    double,     //accounted
    double      //remaining
    >
{
public:
    TotalsView();
    virtual ~TotalsView(){}

    int budgetId() const {
        return _budgetId;
    }

    void budgetId(int value){
        _budgetId = value;
    }
private:
    int _budgetId;

    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_TOTALSVIEW_H
