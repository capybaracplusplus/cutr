#include <drogon/drogon.h>
#include <app_factory.h>

int main() {
    drogon::app().loadConfigFile("../config.json");
    cutr::AppFactory::init();
    drogon::app().run();

    return 0;
}