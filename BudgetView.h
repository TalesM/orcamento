#ifndef _ORCA_BUDGETVIEW_H_
#define _ORCA_BUDGETVIEW_H_

#include "OrcaView.h"

class BudgetView: public OrcaView<int, std::string, int, int>
{
public:
    BudgetView();
    virtual ~BudgetView(){}
};


#endif // _ORCA_BUDGETVIEW_H_

