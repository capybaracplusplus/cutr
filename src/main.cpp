#include <drogon/drogon.h>
#include <app_factory.h>

int main() {
    cutr::AppConfig::init();
    drogon::app().loadConfigFile("../config.json");
    cutr::AppFactory::init();
    drogon::app().run();

    return 0;
}