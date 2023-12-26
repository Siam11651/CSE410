cmake_minimum_required(VERSION 3.5.0)
project(offline-2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(offline-2
    "src/main.cpp"
    "src/scene.cpp"
    "src/space.cpp"
)

target_include_directories(offline-2 PRIVATE "include")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
