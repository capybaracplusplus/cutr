#ifndef CUTR_LINK_CONTROLLER_H
#define CUTR_LINK_CONTROLLER_H

#include <drogon/HttpController.h>
#include <services/link_service.h>
#include <services/redirect_service.h>

class LinkController : public drogon::HttpController<LinkController> {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(LinkController::createShortLink, "/shorten", drogon::Post);
        ADD_METHOD_TO(LinkController::redirectToOriginal, "/{hash}", drogon::Get);
    METHOD_LIST_END

    void setServices(std::shared_ptr<cutr::service::LinkService> link,
                     std::shared_ptr<cutr::service::RedirectService> redirect);

    void createShortLink(const drogon::HttpRequestPtr &req,
                         std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void redirectToOriginal(const drogon::HttpRequestPtr &req,
                            std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                            const std::string &hash);

private:
    std::shared_ptr<cutr::service::LinkService> linkService_;
    std::shared_ptr<cutr::service::RedirectService> redirectService_;
};

#endif //CUTR_LINK_CONTROLLER_H
