#include <catch.hpp>
#include "Manager.hpp"

using namespace orca;

std::unique_ptr<Planner> dumbTest() { return nullptr; }

TEST_CASE("Manager registering", "[controller][class-manager]") {
  Manager manager;
  REQUIRE_THROWS_AS(manager.open("test"), std::logic_error);
  manager.register_filetype("test", dumbTest);
  REQUIRE(manager.is_registered("test"));
  REQUIRE_FALSE(manager.is_registered("test1"));
  REQUIRE_NOTHROW(manager.open("test"));
  REQUIRE_THROWS_AS(manager.open("test2"), std::runtime_error);
}

TEST_CASE("Manager regexing", "[controller][class-manager]") {
  Manager manager;
  manager.register_filetype("test*", dumbTest);
  REQUIRE_FALSE(manager.is_registered("test*"));
  REQUIRE(manager.is_registered("test"));
  REQUIRE(manager.is_registered("TEST"));
  REQUIRE(manager.is_registered("testtt"));
  REQUIRE_FALSE(manager.is_registered("atesta"));
}

TEST_CASE("Manager opening", "[controller][class-manager]") {
  Manager manager;
  manager.register_filetype("dumb-test", dumbTest);
  std::unique_ptr<Planner> answer;
  answer = manager.open("dumb-test");
  REQUIRE(answer == nullptr);
  manager.register_filetype("smart-test",
                            []() { return std::make_unique<Planner>(); });
  answer = manager.open("smart-test");
  REQUIRE(answer != nullptr);
  /*TODO Integration with PlannerSqlite0_5*/
}
