cmake_minimum_required(VERSION 3.5.0)
project(offline_3 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

add_library(offline_3_helper
    "src/glad/glad.c"
    # "src/conc_mesh/box_mesh.cpp"
    # "src/conc_mesh/plane_mesh.cpp"
    # "src/conc_mesh/sphere_mesh.cpp"
    # "src/conc_mesh/triangle_mesh.cpp"
    # "src/conc_scene/rtx_scene.cpp"
    # "src/input.cpp"
    # "src/mesh.cpp"
    # "src/object.cpp"
    # "src/scene.cpp"
    "src/screen.cpp"
    # "src/space.cpp"
    "src/time.cpp"
)

target_include_directories(offline_3_helper PRIVATE "include")
target_link_libraries(offline_3_helper GL glfw)

add_executable(offline_3
    "src/arg_parser.cpp"
    "src/main.cpp"
)

target_include_directories(offline_3 PRIVATE "include")
target_link_libraries(offline_3 offline_3_helper)