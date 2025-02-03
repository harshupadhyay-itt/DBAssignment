#include "../include/SQLiteDB.hpp"
#include <iostream>

int main()
{
    SQLiteDB sqliteDB("test.db");

    if (sqliteDB.create("Hello, SQLite!"))
    {
        std::cout << "Record inserted successfully!\n";
    }
    else
    {
        std::cerr << "Failed to insert record.\n";
    }

    std::cout << "Reading record with ID 1: " << sqliteDB.read(1) << std::endl;

    if (sqliteDB.update(1, "Updated SQLite Record"))
    {
        std::cout << "Record updated successfully!\n";
    }
    else
    {
        std::cerr << "Failed to update record.\n";
    }

    std::cout << "Reading updated record with ID 1: " << sqliteDB.read(1) << std::endl;

    if (sqliteDB.deleteRecord(1))
    {
        std::cout << "Record deleted successfully!\n";
    }
    else
    {
        std::cerr << "Failed to delete record.\n";
    }

    std::cout << "Trying to read deleted record: " << sqliteDB.read(1) << std::endl;

    return 0;
}
