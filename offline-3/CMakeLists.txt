cmake_minimum_required(VERSION 3.5.0)
project(offline_3 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_library(offline_3_helper
    "src/conc_mesh/base_triangle_mesh.cpp"
    "src/conc_mesh/box_mesh.cpp"
    "src/conc_mesh/cylinder_mesh.cpp"
    "src/conc_mesh/plane_mesh.cpp"
    "src/conc_mesh/sphere_surface_mesh.cpp"
    "src/conc_mesh/sphere_mesh.cpp"
    "src/conc_mesh/stl_mesh.cpp"
    "src/conc_collider/box_collider.cpp"
    "src/conc_collider/sphere_collider.cpp"
    "src/mesh.cpp"
    "src/object.cpp"
    "src/physics.cpp"
    "src/scene.cpp"
    "src/screen.cpp"
    "src/space.cpp"
    "src/time.cpp"
)

target_include_directories(offline_3_helper PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_3_helper ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(offline_3
    "src/arg_parser.cpp"
    "src/main.cpp"
)

target_include_directories(offline_3 PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} offline_3_helper)