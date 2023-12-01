cmake_minimum_required(VERSION 3.5.0)
project(offline-1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(offline-1 
    "src/box_mesh.cpp"
    "src/main.cpp"
    "src/mesh.cpp"
    "src/transform.cpp"
    "src/vector.cpp"
)

target_include_directories(offline-1 PRIVATE ${OpenGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} "include")
target_link_libraries(offline-1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
