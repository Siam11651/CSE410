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

add_custom_command(TARGET offline-2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/inputs" "${CMAKE_BINARY_DIR}/inputs")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
