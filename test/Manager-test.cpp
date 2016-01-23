#include <catch.hpp>
#include "Manager.hpp"

using namespace orca;

TEST_CASE("Manager registering", "[controller][class-manager]") {
  Manager manager;
  REQUIRE_THROWS_AS(manager.open("test"), std::logic_error);
  manager.register_filetype("test", []() {});
  REQUIRE(manager.is_registered("test"));
  REQUIRE_NOTHROW(manager.open("test"));
  REQUIRE_THROWS_AS(manager.open("test2"), std::runtime_error);
}
