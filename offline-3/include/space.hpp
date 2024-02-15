#ifndef SPACE_H
#define SPACE_H

class vector3
{
public:
    float x;
    float y;
    float z;
    static vector3 one;

    vector3(const float &_x = 0, const float &_y = 0, const float &_z = 0);
    float get_magnitude() const;
    vector3 get_normalized() const;
    bool operator == (const vector3 &other) const;
    bool operator != (const vector3 &other) const;
    vector3 operator + (const vector3 &other) const;
    vector3 &operator += (const vector3 &other);
    vector3 operator - (const vector3 &other) const;
    vector3 &operator -= (const vector3 &other);
    vector3 operator * (const float &value) const;
    vector3 &operator *= (const float &value);
    vector3 operator / (const float &value) const;
    static vector3 cross(const vector3 &vector_a, const vector3 &vector_b);
    static float dot(const vector3 &vector_a, const vector3 &vector_b);
};

class quaternion
{
public:
    float w;
    float x;
    float y;
    float z;

    quaternion();
    quaternion(const vector3 &_euler_rotation);
    quaternion(const vector3 &_axis, const float &_angle);
    quaternion(const float &_w, const float &_x, const float &_y, const float &_z);
    vector3 get_axis() const;
    float get_angle() const;
    float get_magnitude() const;
    quaternion get_normalized() const;
    vector3 get_rotated_vector(const vector3 &source) const;
    quaternion operator * (const quaternion &other) const;
    static quaternion get_rotation(const vector3 &from, const vector3 &to);
};

class transform
{
public:
    vector3 position;
    quaternion rotation;
    vector3 scale;

    transform();
    transform(const vector3 &_position);
    transform(const vector3 &_position, const vector3 &_euler_rotation);
    transform(const vector3 &_position, const vector3 &_euler_rotation, const vector3 &_scale);
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_left() const;
};

#endif