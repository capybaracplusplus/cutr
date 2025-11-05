include(FetchContent)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
        GIT_TAG        1.9.6
)

FetchContent_MakeAvailable(jsoncpp)
set(JSONCPP_INCLUDE_DIRS "${jsoncpp_SOURCE_DIR}/include" CACHE INTERNAL "")
set(JSONCPP_LIBRARIES jsoncpp_lib CACHE INTERNAL "")