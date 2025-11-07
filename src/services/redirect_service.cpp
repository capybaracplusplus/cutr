#include <services/redirect_service.h>

namespace cutr::service {
    RedirectService::RedirectService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                                     std::shared_ptr<cutr::ILinkRepository> redisRepo)
            : postgresRepo_(std::move(postgresRepo)), redisRepo_(std::move(redisRepo)) {}

    drogon::Task<std::optional<std::string> > RedirectService::getOriginalUrl(const std::string &shortCode) {
        // TODO: Implement this method
        co_return std::nullopt;
    }

    drogon::Task<void> RedirectService::incrementHits(const std::string &shortCode) {
        // TODO: Implement this method
        co_return;
    }

} // namespace cutr::service