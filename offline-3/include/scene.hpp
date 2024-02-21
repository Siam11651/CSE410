#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <space.hpp>
// #include <object.hpp>
#include <cstdint>

namespace o3
{
    class camera
    {
    public:
        o3::transform transform;

        camera();
        camera(const o3::transform &_transform);
    };
}

// class scene
// {
// public:
//     camera *main_camera;
//     std::vector<object *> objects;

//     scene();
//     void setup_frame();
//     void show();
//     virtual void on_new_frame() = 0;
//     virtual void on_new_frame_late() = 0;
//     virtual ~scene();
// };

#endif