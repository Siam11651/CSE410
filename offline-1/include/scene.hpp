#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <space.hpp>
#include <object.hpp>

class camera
{
private:
    transform m_transform;

public:
    camera();
    camera(const transform &camera_transform);
    transform &cam_transform();
    const transform &const_cam_transform() const;
};

class scene
{
protected:
    camera m_main_camera;
    light m_directional_light;
    std::vector<object *> m_objects;

public:
    scene();
    camera &main_camera();
    const camera &const_main_camera() const;
    light &directional_light();
    const light &const_directional_light() const;
    std::vector<object *> &object_ptrs();
    const std::vector<object *> &const_object_ptrs() const;
    void setup_frame();
    void simulate_physics();
    void update_collissions();
    void show();
    virtual void on_new_frame() = 0;
    virtual void on_new_frame_late() = 0;
    virtual void on_ascii_key(uint8_t key, int32_t x, int32_t y) = 0;
    virtual void on_special_key(int32_t key, int32_t x, int32_t y) = 0;
};

#endif