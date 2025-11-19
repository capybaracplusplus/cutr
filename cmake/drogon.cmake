include(cmake/jsoncpp.cmake)

set(BUILD_POSTGRESQL ON CACHE BOOL "Build with postgresql support")
set(BUILD_REDIS ON CACHE BOOL "Build with redis support")
set(BUILD_DOCUMENTATION OFF CACHE BOOL "Disable drogon docs" FORCE)

add_subdirectory(third_party/drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)