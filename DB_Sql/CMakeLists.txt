cmake_minimum_required(VERSION 3.10)
project(DBAbstraction)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

add_executable(db_abstraction_SQL_Lite src/main.cpp src/SQLiteDB.cpp)

target_link_libraries(db_abstraction_SQL_Lite PRIVATE sqlite3)