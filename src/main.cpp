#include <drogon/drogon.h>
#include <app_factory.h>

int main() {
    cutr::AppConfig::init();
    drogon::app().loadConfigFile("../config.json");
    cutr::AppFactory::init();

    drogon::app().registerHandler(
            "/shorten",
            &LinkController::createShortLink,
            {drogon::Post}
    );

    drogon::app().registerHandler(
            "/{hash}",
            &LinkController::redirectToOriginal,
            {drogon::Get}
    );


    drogon::app().run();

    return 0;
}