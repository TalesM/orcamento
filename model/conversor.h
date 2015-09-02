#ifndef _ORCA_MODEL_CONVERSOR_H
#define _ORCA_MODEL_CONVERSOR_H

#include <vector>
#include <SQLiteCpp/Database.h>

bool upgrade(SQLite::Database &db, const std::vector<int> &versionFrom, const std::vector<int> &versionTo);

#endif //_ORCA_MODEL_CONVERSOR_H
