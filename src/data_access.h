#pragma once

#include <string>


class DataAccess
{
public:
    static const char* connectionString;    // Initialized with static value in data_access.cpp

    static int testPostgres();
    static std::string getData();
};
