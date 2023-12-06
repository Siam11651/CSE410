#ifndef CAMERA_H
#define CAMERA_H

#include <vector.hpp>

class transform
{
private:
    const static float DEG2RAD;
    vector3 m_position;
    vector3 m_euler_rotation;

    void rotate(float &x, float &y, float &z) const;

public:
    transform();
    transform(const vector3 &position, const vector3 &euler_rotation);
    vector3 &position();
    vector3 &euler_rotation();
    const vector3 &const_position() const;
    const vector3 &const_euler_rotation() const;
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
};

#endif