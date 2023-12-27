#ifndef SCENE_H
#define SCENE_H

#include <space.hpp>

class view
{
public:
    vector<3> eye;
    vector<3> look;
    vector<3> up;

    view();
    matrix4x4 get_matrix() const;
};

class perspective
{
public:
    double fov;
    double aspect_ratio;
    double far;
    double near;

    perspective();
};

#endif