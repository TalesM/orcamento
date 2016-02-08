#include "MainControllerSqlite0_5.hpp"
#include "sql0_5_0.hpp"

using namespace std;

orca::MainControllerSqlite0_5::MainControllerSqlite0_5(const string &name)
    : a_db(name, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)
{
  SQLite::Transaction transaction(a_db);
  a_db.exec(sql0_5_0);
  transaction.commit();
}

vector<string> orca::MainControllerSqlite0_5::listBudgets() const { return {"stub"}; }
void orca::MainControllerSqlite0_5::flush()
{
  // Should commit...
}
