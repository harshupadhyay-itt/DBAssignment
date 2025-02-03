#ifndef SQLITE_DB_HPP
#define SQLITE_DB_HPP

#include "BaseDB.hpp"
#include <sqlite3.h>
#include <iostream>

class SQLiteDB : public BaseDB
{
private:
    sqlite3 *db;

public:
    SQLiteDB(const std::string &dbName);
    ~SQLiteDB();

    bool create(const std::string &data) override;
    std::string read(int id) override;
    bool update(int id, const std::string &data) override;
    bool deleteRecord(int id) override;
};

#endif
