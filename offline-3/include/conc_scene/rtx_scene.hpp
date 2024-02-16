#ifndef RTX_SCENE_H
#define RTX_SCENE_H

#include <scene.hpp>
#include <object.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/pyramid_mesh.hpp>

class rtx_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_spin;
    plane_mesh *m_plane_mesh;
    sphere_mesh *m_sphere_mesh;
    pyramid_mesh *m_pyramid_mesh;
    object *m_plane_object;
    object *m_sphere_object;
    object *m_pyramid_object;

public:
    rtx_scene();
    void on_new_frame();
    void on_new_frame_late();
};

#endif