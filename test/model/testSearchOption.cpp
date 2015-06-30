#include "../catch.hpp"
#include "model/SearchOption.h"


TEST_CASE("SearchOption", "[model]"){
    REQUIRE(search("teste")->operation() == Operation::NONE);
    CHECK(search("teste")->equal("x")->operation() == Operation::EQUAL);
    CHECK(search("teste")->less("x")->operation() == Operation::LESS);
    CHECK(search("teste")->lessEqual("x")->operation() == Operation::LESS_EQUAL);
    CHECK(search("teste")->different("x")->operation() == Operation::DIFFERENT);
    CHECK(search("teste")->more("x")->operation() == Operation::MORE);
    CHECK(search("teste")->moreEqual("x")->operation() == Operation::MORE_EQUAL);
    CHECK(search("teste")->contains("x")->operation() == Operation::CONTAINS);
    CHECK(search("teste")->prefix("x")->operation() == Operation::PREFIX);
    CHECK(search("teste")->suffix("x")->operation() == Operation::SUFFIX);
    
    CHECK((search("teste")->suffix("x") && search("teste")->prefix("y"))->operation() == Operation::AND);
    CHECK((search("teste")->suffix("x") || search("teste")->prefix("y"))->operation() == Operation::OR);

}