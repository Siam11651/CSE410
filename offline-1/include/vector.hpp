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
    float get_x() const;
    float get_y() const;
    float get_z() const;
    vector3 operator + (const vector3 &other) const;
    vector3 &operator += (const vector3 &other);
};

#endif