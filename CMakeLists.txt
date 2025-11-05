cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0167 NEW)
project(cutr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# <----------------------------- Add Sources ----------------------------->
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/*.h
)

# <----------------------------- Add Executable ----------------------------->
add_executable(${PROJECT_NAME} ${SRC_FILES})

# <----------------------------- Include Dirs ----------------------------->
file(GLOB_RECURSE HANDLER_HEADERS ${CMAKE_SOURCE_DIR}/src/handlers/*.h)
set(HANDLER_DIRS "")
foreach (header ${HANDLER_HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND HANDLER_DIRS ${dir})
endforeach ()
list(REMOVE_DUPLICATES HANDLER_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${HANDLER_DIRS}
        ${CMAKE_SOURCE_DIR}/src
)

# <----------------------------- External Libraries ----------------------------->
include(cmake/drogon.cmake)
