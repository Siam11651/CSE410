#ifndef CAMERA_H
#define CAMERA_H

#include <vector.hpp>
#include <quaternion.hpp>

class transform
{
private:
    vector3 m_position;
    quaternion m_rotation;

public:
    transform();
    transform(const vector3 &position, const vector3 &euler_rotation);
    vector3 &position();
    quaternion &rotation();
    const vector3 &const_position() const;
    const quaternion &const_rotation() const;
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
};

#endif