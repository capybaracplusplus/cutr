#include <repositories/redis/link.h>

namespace cutr::redis {

    LinkRepository::LinkRepository(drogon::nosql::RedisClientPtr redisClient) :
            redisClient_(redisClient) {}

    drogon::Task<std::optional<std::string>> LinkRepository::getOriginalUrl(const std::string &shortCode) try {
        auto key = makeUrlKey(shortCode);

        auto result = co_await redisClient_->execCommandCoro("GET %s", key.c_str());

        if (result.isNil()) {
            co_return std::nullopt;
        }

        co_return result.asString();
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::getOriginalUrl: " << e.what();
        co_return std::nullopt;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::getOriginalUrl";
        co_return std::nullopt;
    }

    drogon::Task<bool> LinkRepository::exists(const std::string &shortCode) try {
        auto key = makeUrlKey(shortCode);

        auto result = co_await redisClient_->execCommandCoro("EXISTS %s", key.c_str());

        co_return result.asInteger() == 1;
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::exists: " << e.what();
        co_return false;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::exists";
        co_return false;
    }

    drogon::Task<bool> LinkRepository::saveLink(const std::string &shortCode, const std::string &originalUrl) try {
        auto key = makeUrlKey(shortCode);

        auto result = co_await redisClient_->execCommandCoro("SET %s %s", key.c_str(), originalUrl.c_str());

        co_return result.asString() == "OK";
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::saveLink: " << e.what();
        co_return false;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::saveLink";
        co_return false;
    }

    drogon::Task<void> LinkRepository::deleteLink(const std::string &shortCode) try {
        auto key = makeUrlKey(shortCode);

        co_await redisClient_->execCommandCoro("DEL %s", key.c_str());

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::deleteLink: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::deleteLink";
        co_return;
    }


    drogon::Task<void> LinkRepository::updateLink(const std::string &shortCode, const std::string &newOriginalUrl) try {
        auto key = makeUrlKey(shortCode);

        co_await redisClient_->execCommandCoro("SET %s %s", key.c_str(), newOriginalUrl.c_str());

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::updateLink: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::updateLink";
        co_return;
    }

    drogon::Task<void> LinkRepository::incrementHits(const std::string &shortCode) try {
        auto key = makeUrlKey(shortCode);

        co_await redisClient_->execCommandCoro("INCR %s", key.c_str());

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::incrementHits: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::incrementHits";
        co_return;
    }

    std::string LinkRepository::makeUrlKey(const std::string &shortCode) {
        return std::string(URL_PREFIX) + shortCode;
    }

    std::string LinkRepository::makeHitsKey(const std::string &shortCode) {
        return std::string(HITS_PREFIX) + shortCode;
    }

    drogon::Task<std::optional<std::string>> LinkRepository::getShortCodeByOriginalUrl(
            const std::string &originalUrl) try {
        auto result = co_await redisClient_->execCommandCoro("HGET ORIGINAL_TO_SHORT %s", originalUrl.c_str());

        if (result.isNil()) {
            co_return std::nullopt;
        }

        co_return result.asString();
    } catch (const std::exception &e) {
        LOG_ERROR << "Redis error in LinkRepository::getShortCodeByOriginalUrl: " << e.what();
        co_return std::nullopt;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::getShortCodeByOriginalUrl";
        co_return std::nullopt;
    }
} // namespace cutr::redis