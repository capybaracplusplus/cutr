#ifndef CUTR_LINK_POSTGRES_H
#define CUTR_LINK_POSTGRES_H

#include <interfaces/i_link_repository.h>
#include <drogon/orm/DbClient.h>
#include <drogon/utils/coroutine.h>

namespace cutr::postgres {
    class LinkRepository : public cutr::ILinkRepository {
    public:
        explicit LinkRepository(drogon::orm::DbClientPtr dbClient);

        drogon::Task<std::optional<std::string>> getOriginalUrl(const std::string &shortCode) override;

        drogon::Task<bool> exists(const std::string &shortCode) override;

        drogon::Task<bool> saveLink(const std::string &shortCode, const std::string &originalUrl) override;

        drogon::Task<void> deleteLink(const std::string &shortCode) override;

        drogon::Task<void> updateLink(const std::string &shortCode, const std::string &newOriginalUrl) override;

        drogon::Task<void> incrementHits(const std::string &shortCode) override;

        drogon::Task<std::optional<std::string>> getShortCodeByOriginalUrl(const std::string &originalUrl) override;

    private:
        drogon::orm::DbClientPtr dbClient_;
    };
} // namespace cutr::postgres

#endif //CUTR_LINK_POSTGRES_H
