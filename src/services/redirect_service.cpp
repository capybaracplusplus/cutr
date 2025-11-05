#include <services/redirect_service.h>

namespace cutr::service {
    RedirectService::RedirectService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                                     std::shared_ptr<cutr::ILinkRepository> redisRepo) : postgresRepo_(
            std::move(postgresRepo)), redisRepo_(std::move(redisRepo)) {}
} // namespace cutr::service