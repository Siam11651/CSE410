cmake_minimum_required(VERSION 3.5.0)
project(offline_3 VERSION 0.1.0 LANGUAGES C CXX)

if(MSVC)
    add_compile_options(/bigobj)
endif()

include(CTest)
enable_testing()

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_library(offline_3_helper
    "src/glad/glad.c"
    "src/scene.cpp"
    "src/screen.cpp"
    "src/space.cpp"
    "src/time.cpp"
)

target_include_directories(offline_3_helper PRIVATE "include")
target_link_libraries(offline_3_helper glfw glm::glm)

add_executable(offline_3
    "src/main.cpp"
)

target_include_directories(offline_3 PRIVATE "include")
target_link_libraries(offline_3 offline_3_helper)