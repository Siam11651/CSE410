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
private:
    camera m_main_camera;
    std::vector<object> m_objects;

public:
    scene();
    camera &main_camera();
    std::vector<object> &objects();
    const camera &const_main_camera() const;
    const std::vector<object> &const_objects() const;
    void show();
};

#endif