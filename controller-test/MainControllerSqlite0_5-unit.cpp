#include <catch.hpp>
#include "MainControllerSqlite0_5.hpp"

using namespace orca;

TEST_CASE("MainControllerSqlite0_5 new file", "[controller][planner][class-maincontrollersqlite0_5][unit]")
{
  MainControllerSqlite0_5 planner{""};
  auto &db = planner.db();

  INFO("Number of Tables" << (int)db.execAndGet("SELECT COUNT(name) FROM sqlite_master WHERE "
                                                "type='table'"))
  auto checkTable = [&db](const string &name) -> int {
    return db.execAndGet(
               "SELECT COUNT(name) FROM sqlite_master WHERE "
               "type='table' AND name like '" +
               name + "'");
  };
  REQUIRE(checkTable("meta"));
  REQUIRE(checkTable("budget"));
  std::string format_name = db.execAndGet("SELECT value FROM meta WHERE key = 'format-name'");
  REQUIRE(format_name == "orcamento");

  std::string format_version = db.execAndGet("SELECT value FROM meta WHERE key = 'format-version'");
  REQUIRE(format_version == "0.5.0");
  REQUIRE(planner.format() == "OrcaMento file format 0.5.0");
}

TEST_CASE("MainControllerSqlite0_5 load file", "[controller][planner][class-maincontrollersqlite0_5][unit]")
{
  string filename = tmpnam(nullptr);
  {
    // Creation
    MainControllerSqlite0_5 planner{filename};  // Saving too.
    auto &db = planner.db();
    db.exec("INSERT INTO meta VALUES('test', 'aTest')");
  }
  MainControllerSqlite0_5 planner{filename};
  auto &db = planner.db();

  REQUIRE((int)db.execAndGet("SELECT COUNT(name) FROM sqlite_master WHERE "
                             "type='table' AND name like 'meta'") == 1);
  std::string format_name = db.execAndGet("SELECT value FROM meta WHERE key = 'test'");
  REQUIRE(format_name == "aTest");
}

TEST_CASE("MainControllerSqlite0_5 listBudgets", "[controller][planner][class-maincontrollersqlite0_5][unit]")
{
  MainControllerSqlite0_5 planner{""};
  auto &db = planner.db();
  std::vector<std::string> vec = planner.listBudgets();
  REQUIRE(vec.size() == 1);
}
