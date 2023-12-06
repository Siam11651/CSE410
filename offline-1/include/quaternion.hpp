#ifndef QUATERNION_H
#define QUATERNION_H

#include <vector.hpp>

class quaternion
{
private:
    float m_w, m_x, m_y, m_z;

public:
    quaternion();
    quaternion(const vector3 &axis, const float &angle);
    quaternion(const float &w, const float &x, const float &y, const float &z);
    float &w();
    float &x();
    float &y();
    float &z();
    const float &const_w() const;
    const float &const_x() const;
    const float &const_y() const;
    const float &const_z() const;
    vector3 rotate(const vector3 &source) const;
    quaternion operator * (const quaternion &other) const;
};

#endif