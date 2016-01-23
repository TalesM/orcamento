#include <catch.hpp>
#include "Manager.hpp"

using namespace orca;

std::unique_ptr<Planner> dumbTest() { return nullptr; }

TEST_CASE("Manager registering", "[controller][class-manager]") {
  Manager manager;
  REQUIRE_THROWS_AS(manager.open("test"), std::logic_error);
  manager.register_filetype("test", dumbTest);
  REQUIRE(manager.is_registered("test"));
  REQUIRE_NOTHROW(manager.open("test"));
  REQUIRE_THROWS_AS(manager.open("test2"), std::runtime_error);
}

TEST_CASE("Manager opening", "[controller][class-manager]") {
  Manager manager;
  manager.register_filetype("dumb-test", dumbTest);
  REQUIRE(manager.open("dumb-test") == nullptr);
  /*TODO A no so dumb test with a mocking of Planner and some way to link it
   * with PlannerSqlite0_5*/
}
