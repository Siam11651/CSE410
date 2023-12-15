#include <conc_scene/magic_cube_scene.hpp>
#include <conc_mesh/base_triangle_mesh.hpp>
#include <conc_mesh/cylinder_mesh.hpp>
#include <conc_mesh/sphere_surface_mesh.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <time.hpp>
#include <GL/freeglut.h>
#include <cmath>
#include <algorithm>

void magic_cube_scene::rescale()
{
    // triangle scale
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
    // triangle translate
    m_left_rear_top_object->object_transform().position() = vector3(1.0f, 1.0f, 1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_right_rear_top_object->object_transform().position() = vector3(-1.0f, 1.0f, 1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_left_front_top_object->object_transform().position() = vector3(1.0f, 1.0f, -1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_right_front_top_object->object_transform().position() = vector3(-1.0f, 1.0f, -1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_left_rear_bot_object->object_transform().position() = vector3(1.0f, -1.0f, 1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_right_rear_bot_object->object_transform().position() = vector3(-1.0f, -1.0f, 1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_left_front_bot_object->object_transform().position() = vector3(1.0f, -1.0f, -1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    m_right_front_bot_object->object_transform().position() = vector3(-1.0f, -1.0f, -1.0f)
        * (1.0f - m_scale_multiple) / 3.0f;
    // sphere scale
    m_sphere_surface_top->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    m_sphere_surface_bot->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    m_sphere_surface_left->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    m_sphere_surface_right->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    m_sphere_surface_rear->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    m_sphere_surface_front->object_transform().scale() = vector3::one * (1.0f - m_scale_multiple)
        / std::sqrt(3.0f);
    // sphere translate
    m_sphere_surface_top->object_transform().position().y() = m_scale_multiple;
    m_sphere_surface_bot->object_transform().position().y() = -m_scale_multiple;
    m_sphere_surface_left->object_transform().position().x() = m_scale_multiple;
    m_sphere_surface_right->object_transform().position().x() = -m_scale_multiple;
    m_sphere_surface_rear->object_transform().position().z() = m_scale_multiple;
    m_sphere_surface_front->object_transform().position().z() = -m_scale_multiple;
    // cylinder scale
    m_clndr_top_front->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_top_rear->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_bot_front->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_bot_rear->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_top_left->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_top_right->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_bot_left->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_bot_right->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_left_rear->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_right_rear->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_left_front->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    m_clndr_right_front->object_transform().scale() = vector3((1.0f - m_scale_multiple) / std::sqrt(3.0f),
        (1.0f - m_scale_multiple) / std::sqrt(3.0f), m_scale_multiple * std::sqrt(2.0f));
    // cylinder translate
    m_clndr_top_front->object_transform().position() = vector3(0.0f, m_scale_multiple / 2.0f,
        -m_scale_multiple / 2.0f);
    m_clndr_top_rear->object_transform().position() = vector3(0.0f, m_scale_multiple / 2.0f,
        m_scale_multiple / 2.0f);
    m_clndr_bot_front->object_transform().position() = vector3(0.0f, -m_scale_multiple / 2.0f,
        -m_scale_multiple / 2.0f);
    m_clndr_bot_rear->object_transform().position() = vector3(0.0f, -m_scale_multiple / 2.0f,
        m_scale_multiple / 2.0f);
    m_clndr_top_left->object_transform().position() = vector3(m_scale_multiple / 2.0f,
        m_scale_multiple / 2.0f, 0.0f);
    m_clndr_top_right->object_transform().position() = vector3(-m_scale_multiple / 2.0f,
        m_scale_multiple / 2.0f, 0.0f);
    m_clndr_bot_left->object_transform().position() = vector3(m_scale_multiple / 2.0f,
        -m_scale_multiple / 2.0f, 0.0f);
    m_clndr_bot_right->object_transform().position() = vector3(-m_scale_multiple / 2.0f,
        -m_scale_multiple / 2.0f, 0.0f);
    m_clndr_left_rear->object_transform().position() = vector3(m_scale_multiple / 2.0f,
        0.0f, m_scale_multiple / 2.0f);
    m_clndr_right_rear->object_transform().position() = vector3(-m_scale_multiple / 2.0f,
        0.0f, m_scale_multiple / 2.0f);
    m_clndr_left_front->object_transform().position() = vector3(m_scale_multiple / 2.0f,
        0.0f, -m_scale_multiple / 2.0f);
    m_clndr_right_front->object_transform().position() = vector3(-m_scale_multiple / 2.0f,
        0.0f, -m_scale_multiple / 2.0f);
}

magic_cube_scene::magic_cube_scene()
{
    m_camera_speed = 5.0f;
    m_camera_rotation_speed = 3.0f;
    m_scale_multiple = 1.0f;
    m_rescale_speed = 1.0f;
    m_ohsp_rotation_speed = 3.0f;
    base_triangle_mesh vertical_mesh(color(1.0f, 0.0f, 1.0f, 1.0f));
    base_triangle_mesh horizontal_mesh(color(color(0.0f, 1.0f, 1.0f, 1.0f)));
    transform object_transform;
    m_left_rear_top_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_right_rear_top_object = new object(horizontal_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_right_front_top_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_left_front_top_object = new object(horizontal_mesh, object_transform);
    object_transform.scale().y() *= -1.0f;
    m_left_front_bot_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_left_rear_bot_object = new object(horizontal_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_right_rear_bot_object = new object(vertical_mesh, object_transform);
    object_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -M_PI / 2.0f)
        * object_transform.rotation();
    m_right_front_bot_object = new object(horizontal_mesh, object_transform);
    // sphere surfaces
    sphere_surface_mesh y_sphere_surface_mesh(1.0f, 25, color(1.0f, 0.0f, 0.0f, 1.0f));
    sphere_surface_mesh x_sphere_surface_mesh(1.0f, 25, color(0.0f, 0.0f, 1.0f, 1.0f));
    sphere_surface_mesh z_sphere_surface_mesh(1.0f, 25, color(0.0f, 1.0f, 0.0f, 1.0f));
    transform surface_transform;
    surface_transform.scale() = vector3();
    surface_transform.position() = vector3(0.0f, 1.0f, 0.0f);
    m_sphere_surface_top = new object(y_sphere_surface_mesh, surface_transform);
    surface_transform.position() = vector3(0.0f, -1.0f, 0.0f);
    surface_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), M_PI);
    m_sphere_surface_bot = new object(y_sphere_surface_mesh, surface_transform);
    surface_transform.position() = vector3(1.0f, 0.0f, 0.0f);
    surface_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), -M_PI / 2.0f);
    m_sphere_surface_left = new object(x_sphere_surface_mesh, surface_transform);
    surface_transform.position() = vector3(-1.0f, 0.0f, 0.0f);
    surface_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 2.0f);
    m_sphere_surface_right = new object(x_sphere_surface_mesh, surface_transform);
    surface_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), M_PI / 2.0f)
        * quaternion(vector3(0.0f, 1.0f, 0.0f), 0.0f * M_PI / 4.0f);
    surface_transform.position() = vector3(0.0f, 0.0f, 1.0f);
    m_sphere_surface_rear = new object(z_sphere_surface_mesh, surface_transform);
    surface_transform.position() = vector3(0.0f, 0.0f, -1.0f);
    surface_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), -M_PI / 2.0f);
    m_sphere_surface_front = new object(z_sphere_surface_mesh, surface_transform);
    // cylinders
    cylinder_mesh clndr_mesh(1.0f, 1.0f, 10, M_PI - std::acos(-1.0f / 3.0f),
        color(1.0f, 1.0f, 0.0f, 1.0f));
    transform clndr_transform;
    clndr_transform.scale() = vector3(0.0f, 0.0f, 1.0f);
    clndr_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), -M_PI / 4.0f);
    clndr_transform.position() = vector3(0.0f, 0.5f, -0.5f);
    m_clndr_top_front = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), M_PI / 4.0f);
    clndr_transform.position() = vector3(0.0f, 0.5f, 0.5f);
    m_clndr_top_rear = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), -3.0f * M_PI / 4.0f);
    clndr_transform.position() = vector3(0.0f, -0.5f, -0.5f);
    m_clndr_bot_front = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(1.0f, 0.0f, 0.0f), 3.0f * M_PI / 4.0f);
    clndr_transform.position() = vector3(0.5f, 0.5f, 0.0f);
    m_clndr_bot_rear = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), -M_PI / 4.0f)
        * quaternion(vector3(0.0f, 1.0f, 0.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(-0.5f, 0.5f, 0.0f);
    m_clndr_top_left = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 4.0f)
        * quaternion(vector3(0.0f, 1.0f, 0.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(-0.5f, 0.5f, 0.0f);
    m_clndr_top_right = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), -3.0f * M_PI / 4.0f)
        * quaternion(vector3(0.0f, 1.0f, 0.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(-0.5f, -0.5f, 0.0f);
    m_clndr_bot_left = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 0.0f, 1.0f), 3.0f * M_PI / 4.0f)
        * quaternion(vector3(0.0f, 1.0f, 0.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(-0.5f, -0.5f, 0.0f);
    m_clndr_bot_right = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), 3.0f * M_PI / 4.0f)
        * quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(0.5f, 0.0f, -0.5f);
    m_clndr_left_rear = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), M_PI / 4.0f)
        * quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(0.5f, 0.0f, -0.5f);
    m_clndr_right_rear = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), -3.0f * M_PI / 4.0f)
        * quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(0.5f, 0.0f, -0.5f);
    m_clndr_left_front = new object(clndr_mesh, clndr_transform);
    clndr_transform.rotation() = quaternion(vector3(0.0f, 1.0f, 0.0f), - M_PI / 4.0f)
        * quaternion(vector3(0.0f, 0.0f, 1.0f), M_PI / 2.0f);
    clndr_transform.position() = vector3(-0.5f, 0.0f, -0.5f);
    m_clndr_right_front = new object(clndr_mesh, clndr_transform);
    // parent
    m_octahedrosphere = new object();

    m_octahedrosphere->child_ptrs().insert(m_octahedrosphere->child_ptrs().end(),
    {
        m_left_rear_top_object,
        m_right_rear_top_object,
        m_left_front_top_object,
        m_right_front_top_object,
        m_left_rear_bot_object,
        m_right_rear_bot_object,
        m_left_front_bot_object,
        m_right_front_bot_object,
        m_sphere_surface_top,
        m_sphere_surface_bot,
        m_sphere_surface_left,
        m_sphere_surface_right,
        m_sphere_surface_rear,
        m_sphere_surface_front,
        m_clndr_top_front,
        m_clndr_top_rear,
        m_clndr_bot_front,
        m_clndr_bot_rear,
        m_clndr_top_left,
        m_clndr_top_right,
        m_clndr_bot_left,
        m_clndr_bot_right,
        m_clndr_left_rear,
        m_clndr_right_rear,
        m_clndr_left_front,
        m_clndr_right_front
    });
    // camera
    transform main_camera_transform(vector3(0.0f, 0.0f, -3.0f),
        vector3(0.0f, 0.0f, 0.0f));
    camera main_camera(main_camera_transform);
    this->main_camera() = main_camera;
    std::vector<object *> &scene_objects = this->object_ptrs();
    
    scene_objects.insert(scene_objects.end(),
    {
        m_octahedrosphere
    });
}

void magic_cube_scene::on_new_frame()
{

}

void magic_cube_scene::on_new_frame_late()
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
    else if(key == 'a')
    {
        transform &ohsp_transform = m_octahedrosphere->object_transform();
        quaternion &ohsp_rotation = ohsp_transform.rotation();
        ohsp_rotation = quaternion(ohsp_transform.get_up(), m_ohsp_rotation_speed
            * time::delta_time_s()) * ohsp_rotation;
    }
    else if(key == 'd')
    {
        transform &ohsp_transform = m_octahedrosphere->object_transform();
        quaternion &ohsp_rotation = ohsp_transform.rotation();
        ohsp_rotation = quaternion(ohsp_transform.get_up(), -m_ohsp_rotation_speed
            * time::delta_time_s()) * ohsp_rotation;
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