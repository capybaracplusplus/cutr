#ifndef CUTR_I_LINK_REPOSITORY_H
#define CUTR_I_LINK_REPOSITORY_H

#include <optional>
#include <string>
#include <drogon/utils/coroutine.h>

namespace cutr {
    class ILinkRepository {
    public:
        virtual ~ILinkRepository() = default;

        virtual drogon::Task<std::optional<std::string>>
        getOriginalUrl(const std::string &shortCode) = 0;

        virtual drogon::Task<bool>
        saveLink(const std::string &shortCode, const std::string &originalUrl) = 0;

        virtual drogon::Task<void>
        deleteLink(const std::string &shortCode) = 0;

        virtual drogon::Task<bool>
        exists(const std::string &shortCode) = 0;

        virtual drogon::Task<void>
        updateLink(const std::string &shortCode, const std::string &newOriginalUrl) = 0;

        virtual drogon::Task<void>
        incrementHits(const std::string &shortCode) = 0;

        virtual drogon::Task<std::optional<std::string>>
        getShortCodeByOriginalUrl(const std::string &originalUrl) = 0;
    };

} // namespace cutr


#endif //CUTR_I_LINK_REPOSITORY_H
