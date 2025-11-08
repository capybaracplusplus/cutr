#include <utils/shortener.h>
#include <random>
#include <string>

std::string cutr::utils::Shortener::generate(const std::string &input) {
    static constexpr char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    static thread_local std::mt19937 rng(std::random_device{}());
    static thread_local std::uniform_int_distribution<std::size_t> dist(0, sizeof(charset) - 2);

    constexpr std::size_t LENGTH = 6;
    std::string code;
    code.reserve(LENGTH);

    for (std::size_t i = 0; i < LENGTH; ++i) {
        code += charset[dist(rng)];
    }

    return code;
}
