#include "CategoryView.h"

static auto sql = "SELECT name FROM category ORDER BY category_id";

CategoryView::CategoryView():
    OrcaView(sql)
{
    //ctor
}

CategoryView::~CategoryView()
{
    //dtor
}
