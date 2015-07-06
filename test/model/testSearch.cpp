#include "../catch.hpp"
#include "model/Search.h"
using namespace std;

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
    CHECK((search("teste")->suffix("x")->not_())->operation() == Operation::NOT);

    const char *values[] = {
        "NONE",
        "EQUAL",
        "LESS",
        "LESS_EQUAL",
        "DIFFERENT",
        "MORE",
        "MORE_EQUAL",
        "CONTAINS",
        "PREFIX",
        "SUFFIX",
        "AND",
        "OR",
        "NOT",
    };
    auto linearizator = [values](string a, Operation o, string b="")-> string {
        return a + " " + (b.size()?b + " ":"") + values[int(o)];
    }; 
    CHECK(linearize(search("teste"), linearizator) == "teste NONE");
    CHECK(linearize(search("teste")->equal("x"), linearizator) == string("teste x EQUAL"));
    CHECK(linearize(search("teste")->equal("x")->contains("y"), linearizator) == string("teste x EQUAL teste y CONTAINS AND"));
    CHECK(linearize(search("teste")->equal("x")->contains("y")->not_(), linearizator) == string("teste x EQUAL teste y CONTAINS AND NOT"));
    
    SearchQuery sq = sqlize(search("teste")->equal("x"));
    CHECK(sq.query == "");
    CHECK(sq.sValues.size() == 0);
    
    sq = sqlize(search("teste")->equal("x"), {{"teste"}});
    REQUIRE(sq.query == "teste = :s_1");
    REQUIRE(sq.sValues.size() == 1);
    CHECK(sq.sValues[0] == "x");
    
    sq = sqlize(search("teste")->equal("5"), {{"teste", FieldDescriptor::INT}});
    CHECK(sq.query == "teste = :i_1");
    REQUIRE(sq.iValues.size() == 1);
    CHECK(sq.iValues[0] == 5);
    
    sq = sqlize(search("teste")->equal("x")->contains("x"), {{"teste"}});
    REQUIRE(sq.query == "(teste = :s_2 AND teste LIKE :s_1)");//TODO: REPLACE for a regex.
    REQUIRE(sq.sValues.size() == 2);
    CHECK(sq.sValues.at(0) == "%x%");
    CHECK(sq.sValues.at(1) == "x");
    
    sq = sqlize(search("teste")->equal("x"), {{"teste", "t.name"}});
    REQUIRE(sq.query == "t.name = :s_1");
    
    sq = sqlize(search("teste")->equal("5"), {{"teste", "t.name", FieldDescriptor::INT}});
    REQUIRE(sq.query == "t.name = :i_1");
    
    sq = sqlize(search("teste")->equal("5")->not_(), {{"teste", "t.name", FieldDescriptor::INT}});
    REQUIRE(sq.query == "NOT(t.name = :i_1)");
}