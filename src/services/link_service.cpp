#include <services/link_service.h>

namespace cutr::service {
    LinkService::LinkService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                             std::shared_ptr<cutr::ILinkRepository> redisRepo)
            : postgresRepo_(std::move(postgresRepo)), redisRepo_(std::move(redisRepo)) {}

    drogon::Task<std::string> LinkService::createShortLink(const std::string &originalUrl) {
        // TODO: Implement this method
        co_return std::string{};
    }

    drogon::Task<bool> LinkService::shortLinkExists(const std::string &originalUrl) {
        // TODO: Implement this method
        co_return false;
    }

} // namespace cutr::service