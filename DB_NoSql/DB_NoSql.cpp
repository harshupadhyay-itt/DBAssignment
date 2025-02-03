#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>

using namespace mongocxx;
using namespace bsoncxx;
using namespace bsoncxx::builder::stream;

class MongoDBHandler
{
private:
    instance inst{};
    client conn;
    database db;
    collection coll;

public:
    MongoDBHandler(const std::string &uri, const std::string &db_name, const std::string &coll_name)
        : conn(mongocxx::uri{uri}), db(conn[db_name]), coll(db[coll_name]) {}

    void insertDocument(const std::string &name, int age)
    {
        bsoncxx::builder::stream::document doc{};
        doc << "name" << name << "age" << age;
        coll.insert_one(doc.view());
        std::cout << "Document inserted successfully.\n";
    }

    void findAllDocuments()
    {
        auto cursor = coll.find({});
        for (auto &&doc : cursor)
        {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
    }

    void updateDocument(const std::string &name, int newAge)
    {
        bsoncxx::builder::stream::document filter_doc{};
        filter_doc << "name" << name;

        bsoncxx::builder::stream::document update_doc{};
        update_doc << "$set" << open_document << "age" << newAge << close_document;

        coll.update_one(filter_doc.view(), update_doc.view());
        std::cout << "Document updated successfully.\n";
    }

    void deleteDocument(const std::string &name)
    {
        bsoncxx::builder::stream::document filter_doc{};
        filter_doc << "name" << name;
        coll.delete_one(filter_doc.view());
        std::cout << "Document deleted successfully.\n";
    }
};

int main()
{
    MongoDBHandler dbHandler("mongodb://localhost:27017", "test_db", "test_collection");

    int choice;
    while (true)
    {
        std::cout << "\n1. Insert Document\n2. Find All Documents\n3. Update Document\n4. Delete Document\n5. Exit\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::string name;
            int age;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Enter age: ";
            std::cin >> age;
            dbHandler.insertDocument(name, age);
        }
        else if (choice == 2)
        {
            dbHandler.findAllDocuments();
        }
        else if (choice == 3)
        {
            std::string name;
            int newAge;
            std::cout << "Enter name to update: ";
            std::cin >> name;
            std::cout << "Enter new age: ";
            std::cin >> newAge;
            dbHandler.updateDocument(name, newAge);
        }
        else if (choice == 4)
        {
            std::string name;
            std::cout << "Enter name to delete: ";
            std::cin >> name;
            dbHandler.deleteDocument(name);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
