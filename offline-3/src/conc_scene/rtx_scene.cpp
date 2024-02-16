#include <conc_scene/rtx_scene.hpp>
#include <cmath>
#include <input.hpp>
#include <time.hpp>

rtx_scene::rtx_scene() : scene()
{
    m_camera_speed = 2.0f;
    m_camera_spin = 0.5f;
    main_camera = new camera();
    main_camera->cam_transform.position.z = 5.0f;
    main_camera->cam_transform.position.y = 5.0f;
    main_camera->cam_transform.rotation = glm::quat(glm::vec3(-M_PI / 4.0f, 0.0f, 0.0f)) * glm::quat(glm::vec3(0.0f, M_PI, 0.0f));
    m_plane_mesh = new plane_mesh(100, 100, 100, 100);
    m_sphere_mesh = new sphere_mesh(0.5f, 20, 20, color(1.0f, 0.0f, 0.0f, 1.0f));
    m_pyramid_mesh = new pyramid_mesh(1.0f, 0.5f, 0.5f, color(0.0f, 0.0f, 1.0f, 1.0f));
    m_plane_object = new object(*m_plane_mesh);
    m_sphere_object = new object(*m_sphere_mesh);
    m_sphere_object->object_transform.position.y = 0.5f;
    m_pyramid_object = new object(*m_pyramid_mesh);

    objects.push_back(m_plane_object);
    // objects.push_back(m_sphere_object);
    objects.push_back(m_pyramid_object);
}

#include <iostream>

void rtx_scene::on_new_frame()
{
    if(input::get_key(input::key::key_w) == input::status::press)
    {
        main_camera->cam_transform.position += main_camera->cam_transform.get_forward() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_a) == input::status::press)
    {
        main_camera->cam_transform.position += main_camera->cam_transform.get_left() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_s) == input::status::press)
    {
        main_camera->cam_transform.position -= main_camera->cam_transform.get_forward() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_d) == input::status::press)
    {
        main_camera->cam_transform.position -= main_camera->cam_transform.get_left() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_pg_up) == input::status::press)
    {
        main_camera->cam_transform.position += main_camera->cam_transform.get_up() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_pg_down) == input::status::press)
    {
        main_camera->cam_transform.position -= main_camera->cam_transform.get_up() * m_camera_speed * time::delta_time_s();
    }

    if(input::get_key(input::key::key_up) == input::status::press)
    {
        const glm::vec3 &left = main_camera->cam_transform.get_left();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * left.x;
        const float qy = std::sin(angle / 2.0f) * left.y;
        const float qz = std::sin(angle / 2.0f) * left.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }

    if(input::get_key(input::key::key_down) == input::status::press)
    {
        const glm::vec3 &left = main_camera->cam_transform.get_left();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * left.x;
        const float qy = std::sin(angle / 2.0f) * left.y;
        const float qz = std::sin(angle / 2.0f) * left.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }

    if(input::get_key(input::key::key_left) == input::status::press)
    {
        const glm::vec3 &up = main_camera->cam_transform.get_up();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * up.x;
        const float qy = std::sin(angle / 2.0f) * up.y;
        const float qz = std::sin(angle / 2.0f) * up.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }

    if(input::get_key(input::key::key_right) == input::status::press)
    {
        const glm::vec3 &up = main_camera->cam_transform.get_up();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * up.x;
        const float qy = std::sin(angle / 2.0f) * up.y;
        const float qz = std::sin(angle / 2.0f) * up.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }

    if(input::get_key(input::key::key_q) == input::status::press)
    {
        const glm::vec3 &forward = main_camera->cam_transform.get_forward();
        const float angle = -m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * forward.x;
        const float qy = std::sin(angle / 2.0f) * forward.y;
        const float qz = std::sin(angle / 2.0f) * forward.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }

    if(input::get_key(input::key::key_e) == input::status::press)
    {
        const glm::vec3 &forward = main_camera->cam_transform.get_forward();
        const float angle = m_camera_spin * time::delta_time_s();
        const float qw = std::cos(angle / 2.0f);
        const float qx = std::sin(angle / 2.0f) * forward.x;
        const float qy = std::sin(angle / 2.0f) * forward.y;
        const float qz = std::sin(angle / 2.0f) * forward.z;
        main_camera->cam_transform.rotation = glm::quat(qw, qx, qy, qz) * main_camera->cam_transform.rotation;
    }
}

void rtx_scene::on_new_frame_late()
{

}