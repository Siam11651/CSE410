#ifndef SPACE_H
#define SPACE_H

class vector3
{
private:
    float m_x;
    float m_y;
    float m_z;

public:
    vector3(const float &x = 0, const float &y = 0, const float &z = 0);
    float &x();
    float &y();
    float &z();
    const float &const_x() const;
    const float &const_y() const;
    const float &const_z() const;
    float get_magnitude() const;
    vector3 get_normalized() const;
    bool operator == (const vector3 &other) const;
    bool operator != (const vector3 &other) const;
    vector3 operator + (const vector3 &other) const;
    vector3 &operator += (const vector3 &other);
    vector3 operator - (const vector3 &other) const;
    vector3 &operator -= (const vector3 &other);
    vector3 operator * (const float &other) const;
};

class quaternion
{
private:
    float m_w, m_x, m_y, m_z;

public:
    quaternion();
    quaternion(const vector3 &euler_rotation);
    quaternion(const vector3 &axis, const float &angle);
    quaternion(const float &w, const float &x, const float &y, const float &z);
    vector3 get_axis() const;
    float get_angle() const;
    float &w();
    float &x();
    float &y();
    float &z();
    const float &const_w() const;
    const float &const_x() const;
    const float &const_y() const;
    const float &const_z() const;
    vector3 get_post_rotation(const vector3 &source) const;
    quaternion operator * (const quaternion &other) const;
};

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