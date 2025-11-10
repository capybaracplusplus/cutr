#include <controllers/link_controller.h>

std::shared_ptr<cutr::service::LinkService> LinkController::linkService_ = nullptr;
std::shared_ptr<cutr::service::RedirectService> LinkController::redirectService_ = nullptr;

void LinkController::setServices(std::shared_ptr<cutr::service::LinkService> link,
                                 std::shared_ptr<cutr::service::RedirectService> redirect) {
    linkService_ = std::move(link);
    redirectService_ = std::move(redirect);
}


drogon::Task<drogon::HttpResponsePtr> LinkController::createShortLink(
        drogon::HttpRequestPtr req) {
    auto jsonReq = req->getJsonObject();
    if (!jsonReq || !(*jsonReq)["url"].isString()) {
        co_return drogon::HttpResponse::newHttpJsonResponse(
                Json::Value{{"error", "Missing 'url' in request"}}
        );
    }

    std::string originalUrl = (*jsonReq)["url"].asString();
    std::string shortCode = co_await linkService_->createShortLink(originalUrl);

    Json::Value jsonResp;
    jsonResp["shortCode"] = shortCode;
    co_return drogon::HttpResponse::newHttpJsonResponse(jsonResp);
}

drogon::Task<drogon::HttpResponsePtr> LinkController::redirectToOriginal(
        drogon::HttpRequestPtr req,
        const std::string &hash) {
    auto urlOpt = co_await redirectService_->getOriginalUrl(hash);

    if (!urlOpt.has_value()) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k404NotFound);
        resp->setBody("Short link not found");
        co_return resp;
    }

    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k302Found);
    resp->addHeader("Location", *urlOpt);
    co_return resp;
}

