#include "upgrader.h"
#include "sql/translate_0_2_0_to_0_4_0.h"

bool upgrade(SQLite::Database &db, const std::vector<int> &versionFrom, const std::vector<int> &versionTo){
    using namespace std;
    if(versionTo[0] != 0 || versionTo[1] != 4 || versionTo[2] != 0 || versionTo[3]!= 0){
        return false;
    }
    if(versionFrom[0] == 0 && versionFrom[1] == 2 && versionFrom[2] == 0){
        db.exec(v0_4_0::translateFrom0_2_0Script);
        return true;
    }
    return false;
}
