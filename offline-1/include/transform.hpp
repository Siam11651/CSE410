#ifndef CAMERA_H
#define CAMERA_H

#include <vector.hpp>
#include <quaternion.hpp>

class transform
{
private:
    vector3 m_position;
    quaternion m_rotation;
    vector3 m_scale;

public:
    transform();
    transform(const vector3 &position);
    transform(const vector3 &position, const vector3 &euler_rotation);
    transform(const vector3 &position, const vector3 &euler_rotation, const vector3 &scale);
    vector3 &position();
    quaternion &rotation();
    vector3 &scale();
    const vector3 &const_position() const;
    const quaternion &const_rotation() const;
    const vector3 &const_scale() const;
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
};

#endif