#include <services/link_service.h>

namespace cutr::service {
    LinkService::LinkService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                             std::shared_ptr<cutr::ILinkRepository> redisRepo) : postgresRepo_(std::move(postgresRepo)),
                                                                                 redisRepo_(std::move(redisRepo)) {}
} // namespace cutr::service