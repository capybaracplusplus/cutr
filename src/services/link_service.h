#ifndef CUTR_LINK_SERVICE_H
#define CUTR_LINK_SERVICE_H

#include <interfaces/i_link_repository.h>

namespace cutr::service {
    class LinkService {
    public:
        explicit LinkService(std::shared_ptr<cutr::ILinkRepository> postgresRepo,
                             std::shared_ptr<cutr::ILinkRepository> redisRepo);

    private:
        std::shared_ptr<ILinkRepository> redisRepo_;
        std::shared_ptr<ILinkRepository> postgresRepo_;
    };
} // namespace cutr::service

#endif //CUTR_LINK_SERVICE_H
