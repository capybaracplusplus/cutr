include(FetchContent)

FetchContent_Declare(
        dotenv
        GIT_REPOSITORY https://github.com/laserpants/dotenv-cpp.git
)
FetchContent_MakeAvailable(dotenv)

target_link_libraries(${PROJECT_NAME} PRIVATE dotenv)