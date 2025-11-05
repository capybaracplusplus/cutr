#include <models/link.h>

model::Link::Link() = default;

model::Link::Link(std::string sc, std::string url)
        : shortCode(std::move(sc)), originalUrl(std::move(url)), createdAt(std::chrono::system_clock::now()) {}