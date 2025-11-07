#ifndef CUTR_REDIRECT_SERVICE_H
#define CUTR_REDIRECT_SERVICE_H

#include <interfaces/i_link_repository.h>

namespace cutr::service {
    class RedirectService {
    public:
        explicit RedirectService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                                 std::shared_ptr<cutr::ILinkRepository> redisRepo);

        drogon::Task<std::optional<std::string> > getOriginalUrl(const std::string &shortCode);

        drogon::Task<void> incrementHits(const std::string &shortCode);

    private:
        std::shared_ptr<ILinkRepository> redisRepo_;
        std::shared_ptr<ILinkRepository> postgresRepo_;
    };
} // namespace cutr::service

#endif //CUTR_REDIRECT_SERVICE_H
