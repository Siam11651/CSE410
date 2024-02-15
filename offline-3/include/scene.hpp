#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <space.hpp>
#include <object.hpp>
#include <cstdint>

class camera
{
public:
    transform cam_transform;

    camera();
    camera(const transform &_cam_transform);
};

class scene
{
public:
    camera *main_camera;
    std::vector<object *> objects;

    scene();
    void setup_frame();
    void show();
    virtual void on_new_frame() = 0;
    virtual void on_new_frame_late() = 0;
    virtual void on_ascii_key(uint8_t key, int32_t x, int32_t y) = 0;
    virtual void on_special_key(int32_t key, int32_t x, int32_t y) = 0;
    virtual ~scene();
};

#endif