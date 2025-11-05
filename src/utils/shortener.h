#ifndef CUTR_SHORTENER_H
#define CUTR_SHORTENER_H

#include <string>

namespace cutr::utils {
    class Shortener {
    public:
        static std::string generate(const std::string &input);
    };
} // namespace utils

#endif //CUTR_SHORTENER_H
