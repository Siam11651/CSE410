#include <iostream>
#include <GL/freeglut.h>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <cmath>
#include <vector.hpp>
#include <box_mesh.hpp>
#include <transform.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "offline-1"

float aspect_ratio;
std::chrono::steady_clock::time_point frame_begin_time_point;
std::chrono::steady_clock::time_point frame_end_time_point;
double delta_time = 0.0;
box_mesh box_mesh0;
float i = 0.0f;
float s = 30.0f;
transform main_camera_transform(
    vector3(0.0f, 0.0f, -2.0f),
    vector3(0.0f, 180.0f, 0.0f));

void ascii_key_callback(unsigned char key, int x, int y)
{
    std::cout << key << std::endl;

    if(key == '1')
    {

    }
    else if(key == '2')
    {

    }
    else if(key == '3')
    {

    }
    else if(key == '4')
    {

    }
    else if(key == '5')
    {

    }
    else if(key == '6')
    {

    }
}

void special_key_callback(int key, int x, int y)
{
    std::cout << key << std::endl;

    if(key == GLUT_KEY_LEFT)
    {

    }
    else if(key == GLUT_KEY_RIGHT)
    {

    }
    else if(key == GLUT_KEY_UP)
    {

    }
    else if(key == GLUT_KEY_DOWN)
    {

    }
}

void display_callback()  // draw each frame
{
    frame_begin_time_point = std::chrono::steady_clock::now();
    i += s * delta_time;
    vector3 main_camera_position = main_camera_transform.get_position();
    vector3 main_camera_forward = main_camera_transform.get_forward();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(90.0f, aspect_ratio, 0.01f, 100.0f);
    gluLookAt(
        main_camera_position.get_x(), main_camera_position.get_y(), main_camera_position.get_z(),
        main_camera_position.get_x() - main_camera_forward.get_x(),
        main_camera_position.get_y() - main_camera_forward.get_y(),
        main_camera_position.get_z() - main_camera_forward.get_z(),
        0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glRotatef(i, 0.0f, 1.0f, 0.0f);
    box_mesh0.draw();
    glPopMatrix();
    glutSwapBuffers();

    frame_end_time_point = std::chrono::steady_clock::now();
    std::chrono::nanoseconds nanoseconds = frame_end_time_point - frame_begin_time_point;
    delta_time = nanoseconds.count() / 1e9;

    glutPostRedisplay();    // draw next frame
}

int main(int argc, char **argv)
{
    aspect_ratio = (float)WINDOW_WIDTH / WINDOW_HEIGHT;

    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glutDisplayFunc(display_callback);
    glutKeyboardFunc(ascii_key_callback);
    glutSpecialFunc(special_key_callback);
    glutMainLoop();

    return 0;
}