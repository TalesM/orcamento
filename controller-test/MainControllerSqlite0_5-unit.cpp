#include <catch.hpp>
#include "MainControllerSqlite0_5.hpp"

using namespace orca;

TEST_CASE("MainControllerSqlite0_5 creation", "[controller][planner][class-maincontrollersqlite0_5][unit]")
{
  MainControllerSqlite0_5 planner{""};
  auto &db = planner.db();

  REQUIRE((int)db.execAndGet("SELECT COUNT(name) FROM sqlite_master WHERE "
                             "type='table' AND name like 'meta'") == 1);
  std::string format_name = db.execAndGet("SELECT value FROM meta WHERE key = 'format-name'");
  REQUIRE(format_name == "orcamento");

  std::string format_version = db.execAndGet("SELECT value FROM meta WHERE key = 'format-version'");
  REQUIRE(format_version == "0.5.0");
  REQUIRE(planner.format() == "OrcaMento file format 0.5.0");
}

TEST_CASE("MainControllerSqlite0_5 flush", "[controller][planner][class-maincontrollersqlite0_5][unit]") {
  MainControllerSqlite0_5 planner{""};
  auto &db = planner.db();
  std::vector<std::string> vec = planner.listBudgets();
  REQUIRE(vec.size() == 1);
}