#pragma once

#include <drogon/HttpController.h>

namespace api
{
    namespace v1
    {
        class HelloWorld : public drogon::HttpController<HelloWorld>
        {
        public:
            HelloWorld() = default;

            METHOD_LIST_BEGIN
                METHOD_ADD(HelloWorld::get, "", drogon::Get);       //path is /api/v1/
                METHOD_ADD(HelloWorld::cities, "cities", drogon::Get);    //path is /api/v1/cities
            METHOD_LIST_END

            void get(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;
            void cities(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;
        };
    } // namespace v1
} // namespace api