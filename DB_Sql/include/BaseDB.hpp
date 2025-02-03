#ifndef BASE_DB_HPP
#define BASE_DB_HPP

#include <string>

class BaseDB
{
public:
    virtual bool create(const std::string &data) = 0;
    virtual std::string read(int id) = 0;
    virtual bool update(int id, const std::string &data) = 0;
    virtual bool deleteRecord(int id) = 0;
    virtual ~BaseDB() {}
};

#endif
