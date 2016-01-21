#include <catch.hpp>
#include "Manager.hpp"

using namespace orca;

TEST_CASE("Manager", "[controller]") {
  Manager manager;
  REQUIRE_THROWS_AS(manager.open("test"), std::logic_error);
  manager.register_filetype("test", []() {});
}
