#include <conc_scene/magic_cube_scene.hpp>
#include <time.hpp>
#include <GL/freeglut.h>
#include <cmath>
#include <algorithm>

void magic_cube_scene::rescale()
{
    m_left_rear_top_object->object_transform().scale() = vector3(1.0f, 1.0f, 1.0f)
        * m_scale_multiple;
    m_right_rear_top_object->object_transform().scale() = vector3(1.0f, 1.0f, 1.0f)
        * m_scale_multiple;
    m_left_front_top_object->object_transform().scale() = vector3(1.0f, 1.0f, 1.0f)
        * m_scale_multiple;
    m_right_front_top_object->object_transform().scale() = vector3(1.0f, 1.0f, 1.0f)
        * m_scale_multiple;
    m_left_rear_bot_object->object_transform().scale() = vector3(1.0f, -1.0f, 1.0f)
        * m_scale_multiple;
    m_right_rear_bot_object->object_transform().scale() = vector3(1.0f, -1.0f, 1.0f)
        * m_scale_multiple;
    m_left_front_bot_object->object_transform().scale() = vector3(1.0f, -1.0f, 1.0f)
        * m_scale_multiple;
    m_right_front_bot_object->object_transform().scale() = vector3(1.0f, -1.0f, 1.0f)
        * m_scale_multiple;

    m_left_rear_top_object->object_transform().position() = vector3(1.0f, 1.0f, 1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_right_rear_top_object->object_transform().position() = vector3(-1.0f, 1.0f, 1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_left_front_top_object->object_transform().position() = vector3(1.0f, 1.0f, -1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_right_front_top_object->object_transform().position() = vector3(-1.0f, 1.0f, -1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_left_rear_bot_object->object_transform().position() = vector3(1.0f, -1.0f, 1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_right_rear_bot_object->object_transform().position() = vector3(-1.0f, -1.0f, 1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_left_front_bot_object->object_transform().position() = vector3(1.0f, -1.0f, -1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
    m_right_front_bot_object->object_transform().position() = vector3(-1.0f, -1.0f, -1.0f)
        * (1.0f - m_scale_multiple) * 0.5f;
}

magic_cube_scene::magic_cube_scene()
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 3.0f;
    m_scale_multiple = 1.0f;
    m_rescale_speed = 1.0f;
    base_triangle_mesh vertical_mesh(color(1.0f, 0.0f, 1.0f, 1.0f));
    base_triangle_mesh horizontal_mesh(color(color(0.0f, 1.0f, 1.0f, 1.0f)));
    transform object_transform;
    m_left_rear_top_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_right_rear_top_object = new object(horizontal_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_right_front_top_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_left_front_top_object = new object(horizontal_mesh, object_transform);
    object_transform.scale().y() *= -1.0f;
    m_left_front_bot_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_left_rear_bot_object = new object(horizontal_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_right_rear_bot_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -(float)M_PI / 2.0f)
        * object_transform.rotation();
    m_right_front_bot_object = new object(horizontal_mesh, object_transform);
    // camera
    transform main_camera_transform(vector3(0.0f, 0.0f, -1.5f),
        vector3(0.0f, 0.0f, 0.0f));
    camera main_camera(main_camera_transform);
    this->main_camera() = main_camera;
    std::vector<object *> &scene_objects = this->object_ptrs();
    
    scene_objects.insert(scene_objects.end(),
    {
        m_left_rear_top_object,
        m_right_rear_top_object,
        m_left_front_top_object,
        m_right_front_top_object,
        m_left_rear_bot_object,
        m_right_rear_bot_object,
        m_left_front_bot_object,
        m_right_front_bot_object
    });
}

void magic_cube_scene::on_new_frame()
{

}

void magic_cube_scene::on_ascii_key(uint8_t key, int32_t x, int32_t y)
{
    camera &main_camera = this->main_camera();
    transform &main_camera_transform = main_camera.cam_transform();

    if(key == '1')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '2')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_up(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '3')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_left(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '4')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_left(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '5')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            -m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == '6')
    {
        main_camera_transform.rotation() = quaternion(main_camera_transform.get_forward(),
            m_camera_rotation_speed * time::delta_time_s()) * main_camera_transform.rotation();
    }
    else if(key == ',')
    {
        m_scale_multiple -= m_rescale_speed * time::delta_time_s();
        m_scale_multiple = std::clamp(m_scale_multiple, 0.0f, 1.0f);

        rescale();
    }
    else if(key == '.')
    {
        m_scale_multiple += m_rescale_speed * time::delta_time_s();
        m_scale_multiple = std::clamp(m_scale_multiple, 0.0f, 1.0f);

        rescale();
    }
}

void magic_cube_scene::on_special_key(int32_t key, int32_t x, int32_t y)
{
    camera &main_camera = this->main_camera();
    transform &main_camera_transform = main_camera.cam_transform();

    if(key == GLUT_KEY_LEFT)
    {
        main_camera_transform.position() += main_camera_transform.get_left()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        main_camera_transform.position() -= main_camera_transform.get_left()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_forward()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_forward()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_PAGE_UP)
    {
        main_camera_transform.position() += main_camera_transform.get_up()
            * m_camera_speed * time::delta_time_s();
    }
    else if(key == GLUT_KEY_PAGE_DOWN)
    {
        main_camera_transform.position() -= main_camera_transform.get_up()
            * m_camera_speed * time::delta_time_s();
    }
}