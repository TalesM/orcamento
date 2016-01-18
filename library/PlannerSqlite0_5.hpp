#ifndef ORCA_PLANNER_SQLITE_0_5_HPP
#define ORCA_PLANNER_SQLITE_0_5_HPP

#include <SQLiteCpp/SQLiteCpp.h>

namespace orca {
/**
 * Implements a Sqlite Planner for the format 0.5
 */
class PlannerSqlite0_5 {
public:
  SQLite::Database a_db;
  PlannerSqlite0_5(const char *name) : a_db(name) {}
};
} /* orca */

#endif /* end of include guard: ORCA_PLANNER_SQLITE_0_5_HPP */
