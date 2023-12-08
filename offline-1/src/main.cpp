#include <iostream>
#include <GL/freeglut.h>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <vector.hpp>
#include <sphere_mesh.hpp>
#include <transform.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "offline-1"
#define FPS 60.0f

int64_t frame_time_ns;
float aspect_ratio;
std::chrono::steady_clock::time_point frame_begin_time_point;
std::chrono::steady_clock::time_point frame_end_time_point;
double delta_time = 0.0;
sphere_mesh sphere_mesh0(1.0f, 25, 8);
float camera_speed = 1.0f;
float camera_rotation_speed = 1.0f;
transform main_camera_transform(vector3(0.0f, 0.0f, -2.0f),
    vector3(0.0f, 0.0f, 0.0f));

void ascii_key_callback(unsigned char key, int x, int y)
{
    if(key == '1')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            -camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
    else if(key == '2')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
    else if(key == '3')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
            -camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
    else if(key == '4')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
            camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
    else if(key == '5')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
    else if(key == '6')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            -camera_rotation_speed * delta_time) * main_camera_transform.rotation();
    }
}

void special_key_callback(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT)
    {
        main_camera_transform.position() += main_camera_transform.get_right() * camera_speed * delta_time;
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        main_camera_transform.position() -= main_camera_transform.get_right() * camera_speed * delta_time;
    }
    else if(key == GLUT_KEY_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_forward() * camera_speed * delta_time;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_forward() * camera_speed * delta_time;
    }
    else if(key == GLUT_KEY_PAGE_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_up() * camera_speed * delta_time;
    }
    else if(key == GLUT_KEY_PAGE_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_up() * camera_speed * delta_time;
    }
}

void display_callback()  // draw each frame
{
    // if(delta_time > 0)
    // {
    //     std::cout << 1.0f / delta_time << std::endl;
    // }

    frame_begin_time_point = std::chrono::steady_clock::now();
    const vector3 &main_camera_position = main_camera_transform.position();
    const vector3 &main_camera_forward = main_camera_transform.get_forward();
    const vector3 &main_camera_up = main_camera_transform.get_up();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(90.0f, aspect_ratio, 0.01f, 100.0f);
    gluLookAt(
        main_camera_position.const_x(), main_camera_position.const_y(), main_camera_position.const_z(),
        main_camera_position.const_x() + main_camera_forward.const_x(),
        main_camera_position.const_y() + main_camera_forward.const_y(),
        main_camera_position.const_z() + main_camera_forward.const_z(),
        main_camera_up.const_x(), main_camera_up.const_y(), main_camera_up.const_z());
    glPushMatrix();
    sphere_mesh0.draw();
    glPopMatrix();
    glutSwapBuffers();

    frame_end_time_point = std::chrono::steady_clock::now();
    std::chrono::nanoseconds nanoseconds = frame_end_time_point - frame_begin_time_point;

    if(nanoseconds.count() < frame_time_ns)
    {
        std::chrono::nanoseconds sleep_time(frame_time_ns - nanoseconds.count());

        std::this_thread::sleep_for(sleep_time);

        frame_end_time_point = std::chrono::steady_clock::now();
        nanoseconds = frame_end_time_point - frame_begin_time_point;
    }

    delta_time = nanoseconds.count() / 1e9f;

    glutPostRedisplay();    // draw next frame
}

int main(int argc, char **argv)
{
    frame_time_ns = 1e9 / FPS;
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