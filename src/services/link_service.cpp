#include <services/link_service.h>
#include <utils/shortener.h>

namespace cutr::service {
    LinkService::LinkService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                             std::shared_ptr<cutr::ILinkRepository> redisRepo)
            : postgresRepo_(std::move(postgresRepo)), redisRepo_(std::move(redisRepo)) {}

    drogon::Task<std::string> LinkService::createShortLink(const std::string &originalUrl) {
        std::string shortCode;
        bool exists = true;

        while (exists) {
            shortCode = utils::Shortener::generate(originalUrl);

            auto cached = co_await redisRepo_->getOriginalUrl(shortCode);
            if (cached.has_value()) {
                continue;
            }

            exists = co_await postgresRepo_->exists(shortCode);
        }

        co_await postgresRepo_->saveLink(shortCode, originalUrl);
        co_await redisRepo_->saveLink(shortCode, originalUrl);

        co_return shortCode;
    }

    drogon::Task<bool> LinkService::shortLinkExists(const std::string &originalUrl) {
        std::string shortCode = utils::Shortener::generate(originalUrl);

        auto cached = co_await redisRepo_->getOriginalUrl(shortCode);
        if (cached.has_value()) {
            co_return true;
        }

        auto exists = co_await postgresRepo_->exists(shortCode);
        co_return exists;
    }

} // namespace cutr::service