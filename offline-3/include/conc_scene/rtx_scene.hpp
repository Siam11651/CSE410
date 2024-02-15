#ifndef RTX_SCENE_H
#define RTX_SCENE_H

#include <scene.hpp>
#include <object.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/base_triangle_mesh.hpp>

class rtx_scene : public scene
{
private:
    plane_mesh *m_plane_mesh;
    sphere_mesh *m_sphere_mesh;
    base_triangle_mesh *m_base_triangle_mesh;
    object *m_plane_object;
    object *m_sphere_object;
    object *m_base_triangle_object;

public:
    rtx_scene();
    void on_new_frame();
    void on_new_frame_late();
    void on_ascii_key(uint8_t key, int32_t x, int32_t y);
    void on_special_key(int32_t key, int32_t x, int32_t y);
};

#endif