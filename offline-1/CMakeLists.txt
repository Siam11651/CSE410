cmake_minimum_required(VERSION 3.5.0)
project(offline_1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_library(offline_1_helper
    "src/box_mesh.cpp"
    "src/mesh.cpp"
    "src/transform.cpp"
    "src/vector.cpp"
    "src/quaternion.cpp"
)

target_include_directories(offline_1_helper PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_1_helper ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

add_executable(offline_1
    "src/main.cpp"
)

target_include_directories(offline_1 PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline_1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} offline_1_helper)

# tests
set(tests "test0")

foreach(test ${tests})
    add_executable(${test} "tests/${test}.cpp")
    target_include_directories(${test} PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
    target_link_libraries(${test} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} offline_1_helper)
    add_test (NAME ${test} COMMAND ${test})
endforeach ()