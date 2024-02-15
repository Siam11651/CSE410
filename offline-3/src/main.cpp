#include <iostream>
#include <GL/freeglut.h>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <arg_parser.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <scene.hpp>

scene *current_scene = nullptr;

void ascii_key_callback(unsigned char key, int x, int y)
{
    if(current_scene != nullptr)
    {
        current_scene->on_ascii_key(key, x, y);
    }
}

void special_key_callback(int key, int x, int y)
{
    if(current_scene != nullptr)
    {
        current_scene->on_special_key(key, x, y);
    }
}

void display_callback()  // draw each frame
{
    time::start_frame();

    if(current_scene != nullptr)
    {
        current_scene->setup_frame();
        current_scene->on_new_frame();
        current_scene->simulate_physics();
        current_scene->on_new_frame_late();
        current_scene->show();
    }

    glutSwapBuffers();
    glutPostRedisplay();    // draw next frame
    time::end_frame();
}

int main(int argc, char **argv)
{
    arg_parser parser(argv[0]);

    parser.add_value("scene", "roll");
    parser.parse(argc, argv);
    time::initialise();

    screen::window_title() = "offline-1";
    screen::window_width() = 1366;
    screen::window_height() = 768;

    glutInit(&argc, argv);
    glutInitWindowSize(screen::window_width(), screen::window_height());
    glutCreateWindow(screen::window_title().c_str());
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glutDisplayFunc(display_callback);
    glutKeyboardFunc(ascii_key_callback);
    glutSpecialFunc(special_key_callback);

    glutMainLoop();

    delete current_scene;

    return 0;
}