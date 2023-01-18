#include "data_access.h"

#include <sstream>
#include <iostream>
#include <pqxx/pqxx>
#include <json/json.h>

const char* DataAccess::connectionString = "host=localhost port=5432 dbname=postgres";

int DataAccess::testPostgres()
{
    int result = -1;

    try
    {
        // Establish connection to Postgres server using connection string provided
        pqxx::connection connectionObject(connectionString);

        // Start non-transactional worker (auto-commit after each statement)
        pqxx::nontransaction worker(connectionObject);
        worker.exec("DROP TABLE IF EXISTS cities;");
        worker.exec("CREATE TABLE cities (name varchar(80), location point, population int);");
        worker.exec("INSERT INTO cities VALUES ('Zurich', '(35.3, 149.1)', 395790);");
        worker.exec("INSERT INTO cities VALUES ('Paris', '(36.6, 150.1)', 123456);");
        worker.exec("INSERT INTO cities VALUES ('London', '(30.2, 150.1)', 333555);");

        pqxx::result response = worker.exec("SELECT * FROM cities");

        for (size_t i = 0; i < response.size(); i++)
        {
            const pqxx::row row = response[i];
            for (size_t fieldIdx = 0; fieldIdx < row.size(); fieldIdx++)
            {
                pqxx::field field = row[fieldIdx];
                const char* name = field.name();

                std::cout << name << ": ";
                std::cout << field.c_str() << std::endl;

                if (std::strcmp(name, "population") == 0)
                {
                    int population = field.as<int>();
                    std::cout << field.name() << ": (Integer) " << population << std::endl;
                }
            }

            result = 0;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return result;
}

std::string DataAccess::getData()
{
    std::stringstream ss;

    try
    {
        // Establish connection to Postgres server using connection string provided
        pqxx::connection connectionObject(connectionString);

        // Start query transaction
        pqxx::work worker(connectionObject);
        pqxx::result response = worker.exec("SELECT * FROM cities");

        Json::Value root;
        root.append("Cities");

        for (size_t i = 0; i < response.size(); i++)
        {
            Json::Value obj;

            const pqxx::row row = response[i];
            for (size_t fieldIdx = 0; fieldIdx < row.size(); fieldIdx++)
            {
                pqxx::field field = row[fieldIdx];
                const char* name = field.name();
                std::string value = field.c_str();

                obj[name] = value;
            }

            root.append(obj);
        }

        // Serialize JSON to string and append to output stream
        Json::FastWriter fastwriter;
        ss << fastwriter.write(root);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return ss.str();
}