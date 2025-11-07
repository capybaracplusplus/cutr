#ifndef CUTR_APP_FACTORY_H
#define CUTR_APP_FACTORY_H

#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <drogon/nosql/RedisClient.h>

#include <repositories/postgres/link.h>
#include <repositories/redis/link.h>
#include <services/link_service.h>
#include <services/redirect_service.h>
#include <controllers/link_controller.h>
#include <app_config.h>

namespace cutr {
    class AppFactory {
    public:
        static void init() {
            initDbClient();
            initRedisClient();
            initRepositories();
            initServices();
            registerControllers();
        }

    private:
        static inline drogon::orm::DbClientPtr dbClient_;
        static inline drogon::nosql::RedisClientPtr redisClient_;
    private:
        static inline std::shared_ptr<postgres::LinkRepository> postgresRepo_;
        static inline std::shared_ptr<redis::LinkRepository> redisRepo_;
    private:
        static inline std::shared_ptr<service::LinkService> linkService_;
        static inline std::shared_ptr<service::RedirectService> redirectService_;

    private:
        static void initDbClient() {
            dbClient_ = drogon::orm::DbClient::newPgClient(
                    "dbname=" + AppConfig::dbName() +
                    " user=" + AppConfig::dbUser() +
                    " password=" + AppConfig::dbPass() +
                    " host=" + AppConfig::dbHost() +
                    " port=" + std::to_string(AppConfig::dbPort()),
                    10
            );
        }

        static void initRedisClient() {
            redisClient_ = drogon::nosql::RedisClient::newRedisClient(
                    trantor::InetAddress(AppConfig::redisHost(), AppConfig::redisPort()), 10
            );
        }

        static void initRepositories() {
            postgresRepo_ = std::make_shared<postgres::LinkRepository>(dbClient_);
            redisRepo_ = std::make_shared<redis::LinkRepository>(redisClient_);
        }

        static void initServices() {
            linkService_ = std::make_shared<service::LinkService>(postgresRepo_, redisRepo_);
            redirectService_ = std::make_shared<service::RedirectService>(postgresRepo_, redisRepo_);
        }

        static void registerControllers() {
            LinkController::setServices(linkService_, redirectService_);
        }
    };
} // namespace cutr


#endif //CUTR_APP_FACTORY_H
