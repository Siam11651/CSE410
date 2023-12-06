#ifndef CAMERA_H
#define CAMERA_H

#include <vector.hpp>
#include <quaternion.hpp>

class transform
{
private:
    const static float DEG2RAD;
    vector3 m_position;
    quaternion m_quaternion;

public:
    transform();
    transform(const vector3 &position, const vector3 &euler_rotation);
    vector3 &position();
    const vector3 &const_position() const;
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
};

#endif