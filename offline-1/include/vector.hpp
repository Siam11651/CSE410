#ifndef VECTOR_H
#define VECTOR_H

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

#endif