#ifndef MAGIC_CUBE_SCENE_H
#define MAGIC_CUBE_SCENE_H

#include <scene.hpp>
#include <object.hpp>

class magic_cube_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_rotation_speed;
    float m_scale_multiple;
    float m_rescale_speed;
    float m_ohsp_rotation_speed;
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
    object *m_sphere_surface_top;
    object *m_sphere_surface_bot;
    object *m_sphere_surface_left;
    object *m_sphere_surface_right;
    object *m_sphere_surface_rear;
    object *m_sphere_surface_front;
    object *m_clndr_top_rear;
    object *m_clndr_top_front;
    object *m_clndr_top_left;
    object *m_clndr_top_right;
    object *m_clndr_bot_rear;
    object *m_clndr_bot_front;
    object *m_clndr_bot_left;
    object *m_clndr_bot_right;
    object *m_clndr_left_rear;
    object *m_clndr_right_rear;
    object *m_clndr_left_front;
    object *m_clndr_right_front;
    object *m_octahedrosphere;

    void rescale();

public:
    magic_cube_scene();
    void on_new_frame();
    void on_new_frame_late();
    void on_ascii_key(uint8_t key, int32_t x, int32_t y);
    void on_special_key(int32_t key, int32_t x, int32_t y);
};

#endif