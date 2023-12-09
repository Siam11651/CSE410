#include <scene.hpp>
#include <time.hpp>
#include <screen.hpp>
#include <GL/freeglut.h>

camera::camera()
{

}

camera::camera(const transform &camera_transform)
{
    m_transform = camera_transform;
}

transform &camera::cam_transform()
{
    return m_transform;
}

const transform &camera::const_cam_transform() const
{
    return m_transform;
}

scene::scene()
{

}

camera &scene::main_camera()
{
    return m_main_camera;
}

std::vector<object> &scene::objects()
{
    return m_objects;
}

const camera &scene::const_main_camera() const
{
    return m_main_camera;
}

const std::vector<object> &scene::const_objects() const
{
    return m_objects;
}

void scene::setup_frame()
{
    const camera &main_camera = const_main_camera();
    const transform &main_camera_transform = main_camera.const_cam_transform();
    const vector3 &main_camera_position = main_camera_transform.const_position();
    const vector3 &main_camera_forward = main_camera_transform.get_forward();
    const vector3 &main_camera_up = main_camera_transform.get_up();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluPerspective(90.0f, screen::aspect_ratio(), 0.01f, 100.0f);
    gluLookAt(
        main_camera_position.const_x(), main_camera_position.const_y(), main_camera_position.const_z(),
        main_camera_position.const_x() + main_camera_forward.const_x(),
        main_camera_position.const_y() + main_camera_forward.const_y(),
        main_camera_position.const_z() + main_camera_forward.const_z(),
        main_camera_up.const_x(), main_camera_up.const_y(), main_camera_up.const_z());
}

void scene::simulate_physics()
{
    for(object &object_item : m_objects)
    {
        rigidbody *object_rigidbody = object_item.get_rigidbody();

        if(object_rigidbody == nullptr)
        {
            continue;
        }

        if(!object_rigidbody->const_enabled())
        {
            continue;
        }

        const std::optional<collission_event> &opt_collission_event =
            object_rigidbody->const_opt_collission_event();

        if(opt_collission_event.has_value())
        {

        }
        else
        {
            vector3 &object_position = object_item.object_transform().position();
            const vector3 &object_velocity = object_rigidbody->const_velocity();
            object_position += object_velocity * time::delta_time();
        }
    }
}

void scene::show()
{
    for(object &object_item : m_objects)
    {
        object_item.draw();
    }
}