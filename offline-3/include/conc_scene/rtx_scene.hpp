#ifndef RTX_SCENE_H
#define RTX_SCENE_H

#include <fstream>
#include <scene.hpp>
#include <object.hpp>
#include <conc_mesh/plane_mesh.hpp>
#include <conc_mesh/sphere_mesh.hpp>
#include <conc_mesh/triangle_mesh.hpp>

class rtx_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_spin;

public:
    rtx_scene();
    void on_new_frame();
    void on_new_frame_late();
    ~rtx_scene();
};

#endif