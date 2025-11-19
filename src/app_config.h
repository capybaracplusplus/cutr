#ifndef CUTR_APP_CONFIG_H
#define CUTR_APP_CONFIG_H

#include <string>
#include <dotenv.h>

namespace cutr {
    class AppConfig {
    public:
        static void init() {
            dotenv::init("../.env");
        }

        static std::string dbName() { return getEnvOrThrow("POSTGRES_DB"); }

        static std::string dbUser() { return getEnvOrThrow("POSTGRES_USER"); }

        static std::string dbPass() { return getEnvOrThrow("POSTGRES_PASSWORD"); }

        static std::string dbHost() { return "POSTGRES_HOST"; }

        static int dbPort() { return std::stoi(getEnvOrThrow("DB_PORT")); }

        static std::string redisHost() { return getEnvOrThrow("REDIS_HOST"); }

        static int redisPort() { return std::stoi(getEnvOrThrow("REDIS_PORT")); }

        static std::string listenAddr() { return getEnvOrThrow("LISTEN_ADDR"); }

        static int listenPort() { return std::stoi(getEnvOrThrow("LISTEN_PORT")); }

    private:
        static const char *getEnvOrThrow(const char *name) {
            const char *val = std::getenv(name);
            if (!val) {
                throw std::runtime_error(std::string("Environment variable not set: ") + name);
            }
            return val;
        }
    };
} // namespace cutr

#endif //CUTR_APP_CONFIG_H
