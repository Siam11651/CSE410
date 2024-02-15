#include <conc_scene/rtx_scene.hpp>
#include <cmath>

rtx_scene::rtx_scene() : scene()
{
    main_camera = new camera();
    main_camera->cam_transform.position.z = 5.0f;
    main_camera->cam_transform.position.y = 5.0f;
    main_camera->cam_transform.rotation = quaternion(glm::vec3(-M_PI / 4.0f, 0.0f, 0.0f)) * quaternion(glm::vec3(0.0f, M_PI, 0.0f));
    m_plane_mesh = new plane_mesh(100, 100, 100, 100);
    m_sphere_mesh = new sphere_mesh(0.5f, 20, 20, color(1.0f, 0.0f, 0.0f, 1.0f));
    m_plane_object = new object(*m_plane_mesh);
    m_sphere_object = new object(*m_sphere_mesh);
    m_sphere_object->object_transform.position.y = 0.5f;

    objects.push_back(m_plane_object);
    objects.push_back(m_sphere_object);
    // objects.push_back(new object(*new base_triangle_mesh()));
}

void rtx_scene::on_new_frame()
{

}

void rtx_scene::on_new_frame_late()
{

}

void rtx_scene::on_ascii_key(uint8_t key, int32_t x, int32_t y)
{

}

void rtx_scene::on_special_key(int32_t key, int32_t x, int32_t y)
{

}