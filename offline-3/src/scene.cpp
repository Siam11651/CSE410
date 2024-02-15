#include <scene.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <GL/freeglut.h>
#include <functional>
#include <iostream>

camera::camera()
{

}

camera::camera(const transform &_cam_transform)
{
    cam_transform = _cam_transform;
}

scene::scene()
{

}

void scene::setup_frame()
{
    const camera &main_camera = main_camera;
    const transform &main_camera_transform = main_camera.cam_transform;
    const vector3 &main_camera_position = main_camera_transform.position;
    const vector3 &main_camera_forward = main_camera_transform.get_forward();
    const vector3 &main_camera_up = main_camera_transform.get_up();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(45.0f, screen::aspect_ratio(), 0.01f, 100.0f);
    gluLookAt(main_camera_position.x, main_camera_position.y, main_camera_position.z, main_camera_position.x + main_camera_forward.x, main_camera_position.y + main_camera_forward.y, main_camera_position.z + main_camera_forward.z, main_camera_up.x, main_camera_up.y, main_camera_up.z);
}

void scene::show()
{
    for(const object *object_item : objects)
    {
        object_item->draw();
    }
}