#include <repositories/postgres/link.h>

namespace cutr::postgres {

    LinkRepository::LinkRepository(drogon::orm::DbClientPtr dbClient)
            : dbClient_(dbClient) {}

    drogon::Task<std::optional<std::string>> LinkRepository::getOriginalUrl(const std::string &shortCode) try {
        auto result = co_await dbClient_->execSqlCoro(
                "SELECT original_url FROM links WHERE short_code = $1",
                shortCode
        );

        if (result.empty()) {
            co_return std::nullopt;
        }

        co_return result[0]["original_url"].as<std::string>();
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::getOriginalUrl: " << e.what();
        co_return std::nullopt;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::getOriginalUrl";
        co_return std::nullopt;
    }

    drogon::Task<bool> LinkRepository::exists(const std::string &shortCode) try {
        auto result = co_await dbClient_->execSqlCoro(
                "SELECT 1 FROM links WHERE short_code = $1",
                shortCode
        );

        co_return !result.empty();
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::exists: " << e.what();
        co_return false;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::exists";
        co_return false;
    }

    drogon::Task<bool> LinkRepository::saveLink(const std::string &shortCode, const std::string &originalUrl) try {
        co_await dbClient_->execSqlCoro(
                "INSERT INTO links (short_code, original_url) VALUES ($1, $2)",
                shortCode,
                originalUrl
        );

        co_return true;
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::saveLink: " << e.what();
        co_return false;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::saveLink";
        co_return false;
    }

    drogon::Task<void> LinkRepository::deleteLink(const std::string &shortCode) try {
        co_await dbClient_->execSqlCoro(
                "DELETE FROM links WHERE short_code = $1",
                shortCode
        );

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::deleteLink: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::deleteLink";
        co_return;
    }

    drogon::Task<void> LinkRepository::updateLink(const std::string &shortCode, const std::string &newOriginalUrl) try {
        co_await dbClient_->execSqlCoro(
                "UPDATE links SET original_url = $1 WHERE short_code = $2",
                newOriginalUrl,
                shortCode
        );

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::updateLink: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::updateLink";
        co_return;
    }

    drogon::Task<void> LinkRepository::incrementHits(const std::string &shortCode) try {
        co_await dbClient_->execSqlCoro(
                "UPDATE links SET hits = hits + 1 WHERE short_code = $1",
                shortCode
        );

        co_return;
    } catch (const std::exception &e) {
        LOG_ERROR << "Postgres error in LinkRepository::incrementHits: " << e.what();
        co_return;
    } catch (...) {
        LOG_ERROR << "Unknown error in LinkRepository::incrementHits";
        co_return;
    }
} // namespace cutr::postgres