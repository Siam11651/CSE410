#include <iostream>
#include <GL/freeglut.h>
#include <optional>
#include <chrono>
#include <set>
#include <functional>
#include <thread>
#include <cmath>
#include <time.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_collider/sphere_collider.hpp>
#include <scene.hpp>

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "offline-1"

int64_t frame_time_ns;
float aspect_ratio;
float camera_speed = 5.0f;
float camera_rotation_speed = 3.0f;
float ball_speed = 1.0f;
float ball_rotation_speed = 3.0f;
scene current_scene;

void ascii_key_callback(unsigned char key, int x, int y)
{
    camera &main_camera = current_scene.main_camera();
    transform &main_camera_transform = main_camera.cam_transform();
    object &sphere_object = current_scene.objects().front();
    transform &sphere_transform = sphere_object.object_transform();
    quaternion &sphere_rotation = sphere_transform.rotation();
    rigidbody *sphere_rigidbody = sphere_object.get_rigidbody();

    if(key == '1')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            -camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == '2')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == '3')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
            -camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == '4')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_right(),
            camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == '5')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            -camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == '6')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            camera_rotation_speed * time::delta_time()) * main_camera_transform.rotation();
    }
    else if(key == 'j')
    {
        sphere_rotation = quaternion(sphere_transform.get_up(),
            ball_rotation_speed * time::delta_time()) * sphere_rotation;
        sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
            * ball_speed;
    }
    else if(key == 'k')
    {
        sphere_rotation = quaternion(sphere_transform.get_up(),
            -ball_rotation_speed * time::delta_time()) * sphere_rotation;
        sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
            * ball_speed;
    }
}

void special_key_callback(int key, int x, int y)
{
    camera &main_camera = current_scene.main_camera();
    transform &main_camera_transform = main_camera.cam_transform();

    if(key == GLUT_KEY_LEFT)
    {
        main_camera_transform.position() += main_camera_transform.get_right()
            * camera_speed * time::delta_time();
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        main_camera_transform.position() -= main_camera_transform.get_right()
            * camera_speed * time::delta_time();
    }
    else if(key == GLUT_KEY_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_forward()
            * camera_speed * time::delta_time();
    }
    else if(key == GLUT_KEY_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_forward()
            * camera_speed * time::delta_time();
    }
    else if(key == GLUT_KEY_PAGE_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_up()
            * camera_speed * time::delta_time();
    }
    else if(key == GLUT_KEY_PAGE_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_up()
            * camera_speed * time::delta_time();
    }
}

void display_callback()  // draw each frame
{
    // if(delta_time > 0)
    // {
    //     std::cout << 1.0f / delta_time << std::endl;
    // }

    time::start_frame();

    const camera &main_camera = current_scene.const_main_camera();
    const transform &main_camera_transform = main_camera.const_cam_transform();
    const vector3 &main_camera_position = main_camera_transform.const_position();
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
    current_scene.show();
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

    sphere_mesh sphere_mesh0(0.2f, 25, 8);
    transform sphere_transform0(vector3(0.0f, 0.2f, 0.0f));
    object sphere_object(&sphere_mesh0, sphere_transform0);
    sphere_collider rb_sphere_collider(0.2f);
    rigidbody *sphere_rigidbody = new rigidbody(&rb_sphere_collider);
    sphere_object.set_rigidbody(sphere_rigidbody);
    sphere_rigidbody->velocity() = sphere_object.const_object_transform().get_forward()
        * ball_speed;
    plane_mesh plane_mesh0(100.0f, 100.0f, 100, 100);
    object plane_object(&plane_mesh0);
    camera main_camera(vector3(0.0f, 0.5f, -2.0f));
    current_scene.main_camera() = main_camera;
    std::vector<object> &scene_objects = current_scene.objects();
    
    scene_objects.insert(scene_objects.end(),
    {
        sphere_object,
        plane_object
    });

    glutMainLoop();

    return 0;
}