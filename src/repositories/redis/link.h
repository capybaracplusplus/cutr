#ifndef CUTR_LINK_REDiS_H
#define CUTR_LINK_REDiS_H

#include <interfaces/i_link_repository.h>
#include <drogon/nosql/RedisClient.h>
#include <optional>
#include <string>
#include <drogon/utils/coroutine.h>

namespace cutr::redis {
    class LinkRepository : public cutr::ILinkRepository {
    public:
        explicit LinkRepository(drogon::nosql::RedisClientPtr redisClient);

        drogon::Task<std::optional<std::string>> getOriginalUrl(const std::string &shortCode) override;

        drogon::Task<bool> exists(const std::string &shortCode) override;

        drogon::Task<bool> saveLink(const std::string &shortCode, const std::string &originalUrl) override;

        drogon::Task<void> deleteLink(const std::string &shortCode) override;

        drogon::Task<void> updateLink(const std::string &shortCode, const std::string &newOriginalUrl) override;

        drogon::Task<void> incrementHits(const std::string &shortCode) override;

        drogon::Task<std::optional<std::string>> getShortCodeByOriginalUrl(const std::string &originalUrl) override;

    private:
        static constexpr const char *URL_PREFIX = "link:url:";

        static constexpr const char *HITS_PREFIX = "link:hits:";

        static std::string makeUrlKey(const std::string &shortCode);

        static std::string makeHitsKey(const std::string &shortCode);

    private:
        drogon::nosql::RedisClientPtr redisClient_;
    };
} // namespace cutr::redis

#endif //CUTR_LINK_REDiS_H
