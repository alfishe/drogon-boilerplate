#include "gtest/gtest.h"

#include <string>
#include "data_access.h"

TEST(DataAccess, getData)
{
    std::string result = DataAccess::getData();
    EXPECT_EQ(result, "[\"Cities\",{\"location\":\"(35.3,149.1)\",\"name\":\"Zurich\",\"population\":\"395790\"},{\"location\":\"(36.6,150.1)\",\"name\":\"Paris\",\"population\":\"123456\"},{\"location\":\"(30.2,150.1)\",\"name\":\"London\",\"population\":\"333555\"}]\n");
}