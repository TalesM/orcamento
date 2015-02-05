#ifndef _ORCA_BUDGETTOCOPYVIEW_H
#define _ORCA_BUDGETTOCOPYVIEW_H

#include "OrcaView.h"


class BudgetToCopyView : public OrcaView<std::string>
{
public:
    BudgetToCopyView();
    virtual ~BudgetToCopyView(){}
    int sourceBudgetId() const {
        return _sourceBudgetId;
    }

    void sourceBudgetId(int value){
        _sourceBudgetId = value;
    }
private:
    int _sourceBudgetId;

    void setup(SQLite::Statement &stm) override;
};

#endif // _ORCA_BUDGETTOCOPYVIEW_H
