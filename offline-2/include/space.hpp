#ifndef SPACE_H
#define SPACE_H

#include <cstddef>

class vector4
{
public:
    double x;
    double y;
    double z;
    double w;

    vector4();
    vector4(const double &_x, const double &_y, const double &_z, const double &_w);
    vector4 operator + (const vector4 &_other) const;
    vector4 operator - (const vector4 &_other) const;
    vector4 operator * (const double &_scalar) const;
    vector4 operator / (const double &_scalar) const;
    vector4 &operator += (const vector4 &_other);
    vector4 &operator -= (const vector4 &_other);
    vector4 &operator *= (const double &_scalar);
    vector4 &operator /= (const double &_scalar);
    friend vector4 operator * (const double &_scalar, const vector4 &_other);
};

class matrix4x4
{
private:
    vector4 m_vectors[4];

public:
    matrix4x4();
    vector4 &operator [] (const size_t &_index);
    const vector4 &operator [] (const size_t &_index) const;
    matrix4x4 operator * (const matrix4x4 &_other) const;
    vector4 operator * (const vector4 &_other) const;
    matrix4x4 &operator *= (const matrix4x4 &_other);
};

#endif