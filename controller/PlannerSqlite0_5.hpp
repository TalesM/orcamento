#ifndef ORCA_PLANNER_SQLITE_0_5_HPP
#define ORCA_PLANNER_SQLITE_0_5_HPP

#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

namespace orca
{
/**
 * Implements a Sqlite Planner for the format 0.5
 */
class PlannerSqlite0_5
{
  SQLite::Database a_db;

 public:
  PlannerSqlite0_5(const char *name);

  /**
   * Returns a reference to the internal database.
   */
  SQLite::Database &db() { return a_db; }
  SQLite::Database const &db() const { return a_db; }
  std::string format() const { return "OrcaMento file format 0.5.0"; }
};
} /* orca */

#endif /* end of include guard: ORCA_PLANNER_SQLITE_0_5_HPP */
