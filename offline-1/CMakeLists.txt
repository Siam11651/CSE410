cmake_minimum_required(VERSION 3.5.0)
project(offline_1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_library(offline_1_helper
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

target_include_directories(offline_1_helper PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_1_helper ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(offline_1
    "src/arg_parser.cpp"
    "src/conc_scene/magic_cube_scene.cpp"
    "src/conc_scene/rolling_ball_scene.cpp"
    "src/main.cpp"
)

target_include_directories(offline_1 PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} offline_1_helper)

add_custom_command(TARGET offline_1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets")

# tests
set(tests "test0")

foreach(test ${tests})
    add_executable(${test} "tests/${test}.cpp")
    target_include_directories(${test} PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
    target_link_libraries(${test} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} offline_1_helper)
    add_test (NAME ${test} COMMAND ${test})
endforeach ()