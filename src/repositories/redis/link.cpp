#include <repositories/redis/link.h>

namespace cutr::redis {

    LinkRepository::LinkRepository(drogon::nosql::RedisClientPtr redisClient) :
            redisClient_(redisClient) {}

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

    std::string LinkRepository::makeUrlKey(const std::string &shortCode) {
        return std::string(URL_PREFIX) + shortCode;
    }

    std::string LinkRepository::makeHitsKey(const std::string &shortCode) {
        return std::string(HITS_PREFIX) + shortCode;
    }
} // namespace cutr::redis