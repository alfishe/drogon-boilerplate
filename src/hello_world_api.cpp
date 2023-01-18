#include "hello_world_api.h"
#include "data_access.h"

namespace api
{
    namespace v1
    {
        void HelloWorld::get(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const
        {
            Json::Value ret;
            ret["message"] = "Hello, World!";
            auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
            callback(resp);
        }

        void HelloWorld::cities(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const
        {
            auto response(drogon::HttpResponse::newHttpResponse());

            std::string payload = DataAccess::getData();

            response->setStatusCode(drogon::HttpStatusCode::k200OK);
            response->setBody(payload);
            return callback(response);
        }
    }
}