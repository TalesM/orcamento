#include "../catch.hpp"
#include "SearchOption.h"


TEST_CASE("SearchOption", "[model]"){
    auto a = search("");
    REQUIRE(a->operation() == Operation::NONE);

}