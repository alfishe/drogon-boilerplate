#include "hello_world_api.h"
#include "data_access.h"

#include <string>
#include <sstream>
#include <ostream>
#include <pqxx/pqxx>

int main(int argc, char **argv)
{
    LOG_INFO << "Testing Postgres connection";
    if (DataAccess::testPostgres() == 0)
    {
        LOG_INFO << "DB connection ok";
    }
    else
    {
        LOG_ERROR << "DB connection failed";
    }

    LOG_INFO << "Starting server on port 8090 ...";
    LOG_INFO <<  "Use:  http://localhost:8090/api/v1/HelloWorld for static JSON response";
    LOG_INFO <<  "      http://localhost:8090/api/v1/HelloWorld/cities for database data retrieval";

    drogon::app().setLogPath("./")
            .setLogLevel(trantor::Logger::kError)
            .addListener("0.0.0.0", 8090)
            .setThreadNum(6)
            .run();
}