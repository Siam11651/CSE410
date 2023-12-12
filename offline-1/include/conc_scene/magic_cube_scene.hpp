#ifndef MAGIC_CUBE_SCENE_H
#define MAGIC_CUBE_SCENE_H

#include <scene.hpp>
#include <object.hpp>
#include <conc_mesh/base_triangle_mesh.hpp>

class magic_cube_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_rotation_speed;
    float m_scale_multiple;
    float m_rescale_speed;
    vector3 m_initial_top_scale;
    vector3 m_initial_bot_scale;

    object *m_left_rear_top_object;
    object *m_right_rear_top_object;
    object *m_left_front_top_object;
    object *m_right_front_top_object;
    object *m_left_rear_bot_object;
    object *m_right_rear_bot_object;
    object *m_left_front_bot_object;
    object *m_right_front_bot_object;

    void rescale();

public:
    magic_cube_scene();
    void on_new_frame();
    void on_ascii_key(uint8_t key, int32_t x, int32_t y);
    void on_special_key(int32_t key, int32_t x, int32_t y);
};

#endif