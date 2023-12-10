#ifndef ROLLING_BALL_SCENE_H
#define ROLLING_BALL_SCENE_H

#include <scene.hpp>

class rolling_ball_scene : public scene
{
private:
    float m_camera_speed;
    float m_camera_rotation_speed;
    float m_ball_speed;
    float m_effective_ball_speed;
    float m_ball_rotation_speed;

public:
    rolling_ball_scene();
    void on_new_frame();
    void on_ascii_key(uint8_t key, int32_t x, int32_t y);
    void on_special_key(int32_t key, int32_t x, int32_t y);
};

#endif