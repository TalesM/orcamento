#include <catch.hpp>
#include "Manager.hpp"

using namespace orca;

std::unique_ptr<Planner> dumbTest(const std::smatch &) { return nullptr; }

TEST_CASE("Manager registering", "[controller][class-manager][unit]") {
  Manager manager;
  REQUIRE_THROWS_AS(manager.open("test"), std::logic_error);
  manager.register_filetype("test", dumbTest);
  REQUIRE(manager.is_registered("test"));
  REQUIRE_FALSE(manager.is_registered("test1"));
  REQUIRE_NOTHROW(manager.open("test"));
  REQUIRE_THROWS_AS(manager.open("test2"), std::runtime_error);
}

TEST_CASE("Manager regexing", "[controller][class-manager][unit]") {
  Manager manager;
  manager.register_filetype("test*", dumbTest);
  REQUIRE_FALSE(manager.is_registered("test*"));
  REQUIRE(manager.is_registered("test"));
  REQUIRE(manager.is_registered("TEST"));
  REQUIRE(manager.is_registered("testtt"));
  REQUIRE_FALSE(manager.is_registered("atesta"));
}

TEST_CASE("Manager opening", "[controller][class-manager][unit]") {
  Manager manager;
  manager.register_filetype("dumb-test", dumbTest);
  std::unique_ptr<Planner> answer;
  answer = manager.open("dumb-test");
  REQUIRE(answer == nullptr);
  manager.register_filetype("smart-test", [](const std::smatch &) {
    return std::make_unique<Planner>();
  });
  answer = manager.open("smart-test");
  REQUIRE(answer != nullptr);
  /*TODO Integration with PlannerSqlite0_5*/
}

TEST_CASE("Manager opening, regexing", "[controller][class-manager][unit]") {
  Manager manager;
  manager.register_filetype(
      "test([0-9]+)", [](const std::smatch &m) -> std::unique_ptr<Planner> {
        if (m.size() <= 1) {
          return nullptr;
        }
        std::stringstream stream(m[1]);
        CAPTURE(m[0].str());
        CAPTURE(m[1].str());
        int value;
        stream >> value;
        if (value % 2 == 0) {
          return std::make_unique<Planner>();
        }
        return nullptr;
      });
  REQUIRE_FALSE(manager.is_registered("test"));
  REQUIRE(manager.is_registered("test0"));
  REQUIRE(manager.is_registered("TEST1"));
  REQUIRE(manager.is_registered("test350"));
  REQUIRE_THROWS_AS(manager.open("test"), std::runtime_error);
  REQUIRE(manager.open("test0"));
  REQUIRE_FALSE(manager.open("test1"));
  REQUIRE(manager.open("test350"));
}
