#include "../include/SQLiteDB.hpp"

SQLiteDB::SQLiteDB(const std::string &dbName)
{
    if (sqlite3_open(dbName.c_str(), &db))
    {
        std::cerr << "Error opening SQLite DB: " << sqlite3_errmsg(db) << std::endl;
    }
    else
    {
        std::string createTableQuery = "CREATE TABLE IF NOT EXISTS records (id INTEGER PRIMARY KEY, data TEXT);";
        sqlite3_exec(db, createTableQuery.c_str(), 0, 0, 0);
    }
}

SQLiteDB::~SQLiteDB()
{
    sqlite3_close(db);
}

bool SQLiteDB::create(const std::string &data)
{
    std::string query = "INSERT INTO records (data) VALUES (?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_STATIC);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::string SQLiteDB::read(int id)
{
    std::string query = "SELECT data FROM records WHERE id=?;";
    sqlite3_stmt *stmt;
    std::string result = "Not Found";

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        }
    }
    sqlite3_finalize(stmt);
    return result;
}

bool SQLiteDB::update(int id, const std::string &data)
{
    std::string query = "UPDATE records SET data=? WHERE id=?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(stmt, 1, data.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool SQLiteDB::deleteRecord(int id)
{
    std::string query = "DELETE FROM records WHERE id=?;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}
