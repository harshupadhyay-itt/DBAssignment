# DBAssignment

This repository contains assignments related to database concepts, focusing on both SQL and NoSQL databases.

## Contents

- **DB_NoSql**: NoSQL related assignments and implementations.
- **DB_Sql**: SQL-related assignments and solutions.

## Setup

### Clone the repository

git clone https://github.com/harshupadhyay-itt/DBAssignment.git

### Navigate into the project directory

After cloning the branch, run the below command:
cd DBAssignment

### FOR SQLite:
Build the project and Create the build directory:
mkdir build
cd build

Run CMake to configure the build:
cmake ..

Build the project:
cmake --build .

Run the abstraction code:
./db_abstraction



### For NoSQL:

Compile the NoSQL code using g++:
g++ DB_NoSql.cpp -o DB_NoSql $(pkg-config --cflags --libs libmongocxx)

Run the compiled NoSQL program:
./DB_NoSql
