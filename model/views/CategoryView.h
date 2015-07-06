#ifndef _ORCA_CATEGORYVIEW_H
#define _ORCA_CATEGORYVIEW_H

#include "../OrcaView.h"


class CategoryView : public OrcaView<int, std::string>
{
public:
    CategoryView();
    virtual ~CategoryView();
};

#endif // _ORCA_CATEGORYVIEW_H
