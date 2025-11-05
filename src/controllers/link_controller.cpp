#include <controllers/link_controller.h>

void LinkController::setServices(std::shared_ptr<cutr::service::LinkService> link,
                                 std::shared_ptr<cutr::service::RedirectService> redirect) {
    linkService_ = std::move(link);
    redirectService_ = std::move(redirect);
}


void LinkController::createShortLink(const drogon::HttpRequestPtr &req,
                                     std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    // TODO: Implement this method
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setBody("Not implemented yet");
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    callback(resp);
}

void LinkController::redirectToOriginal(const drogon::HttpRequestPtr &req,
                                        std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                                        const std::string &hash) {
    // TODO: Implement this method
    auto resp = drogon::HttpResponse::newHttpResponse();
    resp->setStatusCode(drogon::k200OK);
    resp->setBody("Not implemented yet");
    resp->setContentTypeCode(drogon::CT_TEXT_PLAIN);
    callback(resp);
}