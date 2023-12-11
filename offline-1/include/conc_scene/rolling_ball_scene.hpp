#ifndef ROLLING_BALL_SCENE_H
#define ROLLING_BALL_SCENE_H

#include <scene.hpp>
#include <conc_collider/box_collider.hpp>
#include <conc_collider/sphere_collider.hpp>

class rolling_ball_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_rotation_speed;
    float m_ball_speed;
    float m_effective_ball_speed;
    float m_ball_rotation_speed;
    rigidbody *m_sphere_rigidbody;
    collider *m_sphere_collider;
    box_collider *m_left_wall_collider;
    box_collider *m_right_wall_collider;
    box_collider *m_top_wall_collider;
    box_collider *m_bot_wall_collider;
    object *m_sphere_object;
    object *m_plane_object;
    object *m_left_wall_object;
    object *m_right_wall_object;
    object *m_top_wall_object;
    object *m_bot_wall_object;
    object *m_direction_box;

public:
    rolling_ball_scene();
    void on_new_frame();
    void on_ascii_key(uint8_t key, int32_t x, int32_t y);
    void on_special_key(int32_t key, int32_t x, int32_t y);
};

#endif