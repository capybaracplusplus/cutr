#ifndef CUTR_LINK_H
#define CUTR_LINK_H

#include <string>
#include <chrono>

namespace model {
    class Link {
    public:
        std::string shortCode;
        std::string originalUrl;
        std::chrono::system_clock::time_point createdAt;
        int hits = 0;
    public:
        Link();

        Link(std::string sc, std::string url);
    };
} // namespace model

#endif //CUTR_LINK_H
