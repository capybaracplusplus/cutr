#include <repositories/postgres/link.h>

namespace cutr::postgres {

    LinkRepository::LinkRepository(drogon::orm::DbClientPtr dbClient)
            : dbClient_(dbClient) {}

    drogon::Task<std::optional<std::string>> LinkRepository::getOriginalUrl(const std::string &shortCode) {
        // TODO: Implement this method
        co_return std::nullopt;
    }

    drogon::Task<bool> LinkRepository::exists(const std::string &shortCode) {
        // TODO: Implement this method
        co_return false;
    }

    drogon::Task<bool> LinkRepository::saveLink(const std::string &shortCode, const std::string &originalUrl) {
        // TODO: Implement this method
        co_return false;
    }

    drogon::Task<void> LinkRepository::deleteLink(const std::string &shortCode) {
        // TODO: Implement this method
        co_return;
    }

    drogon::Task<void> LinkRepository::updateLink(const std::string &shortCode, const std::string &newOriginalUrl) {
        // TODO: Implement this method
        co_return;
    }

    drogon::Task<void> LinkRepository::incrementHits(const std::string &shortCode) {
        // TODO: Implement this method
        co_return;
    }
} // namespace cutr::postgres