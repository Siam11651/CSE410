#include <iostream>
#include <GL/freeglut.h>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <time.hpp>
#include <screen.hpp>
#include <conc_scene/rolling_ball_scene.hpp>

#define WINDOW_TITLE "offline-1"

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
        current_scene->simulate_physics();
        current_scene->on_new_frame();
        current_scene->setup_frame();
        current_scene->show();
    }

    // glPushMatrix();
    // glBegin(GL_TRIANGLES);
    // glColor3f(1, 1, 1);
    // glVertex3f(-0.5, 0.0f, 0.5);
    // glVertex3f(-0.5, 0.0f, -0.5);
    // glVertex3f(0.5, 0.0f, 0.5);
    // glEnd();
    // glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();    // draw next frame
    time::end_frame();
}

int main(int argc, char **argv)
{
    screen::window_width() = 1366;
    screen::window_height() = 768;

    glutInit(&argc, argv);
    glutInitWindowSize(screen::window_width(), screen::window_height());
    glutCreateWindow(WINDOW_TITLE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glutDisplayFunc(display_callback);
    glutKeyboardFunc(ascii_key_callback);
    glutSpecialFunc(special_key_callback);

    current_scene = new rolling_ball_scene();

    glutMainLoop();

    return 0;
}