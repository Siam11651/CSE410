#include <space.hpp>

vector4::vector4() :
    x(0.0),
    y(0.0),
    z(0.0),
    w(0.0) {}

vector4::vector4(const double &_x, const double &_y, const double &_z, const double &_w) :
    x(_x),
    y(_y),
    z(_z),
    w(_w) {}

vector4 vector4::operator + (const vector4 &_other) const
{
    return vector4(x + _other.x, y + _other.y, z + _other.z, w + _other.w);
}

vector4 vector4::operator - (const vector4 &_other) const
{
    return vector4(x - _other.x, y - _other.y, z - _other.z, w - _other.w);
}

vector4 vector4::operator * (const double &_scalar) const
{
    return vector4(x * _scalar, y * _scalar, z * _scalar, w * _scalar);
}

vector4 vector4::operator / (const double &_scalar) const
{
    return vector4(x / _scalar, y / _scalar, z / _scalar, w / _scalar);
}

vector4 &vector4::operator += (const vector4 &_other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    w += _other.w;

    return *this;
}

vector4 &vector4::operator -= (const vector4 &_other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    w -= _other.w;

    return *this;
}

vector4 &vector4::operator *= (const double &_scalar)
{
    x *= _scalar;
    y *= _scalar;
    z *= _scalar;
    w *= _scalar;

    return *this;
}

vector4 &vector4::operator /= (const double &_scalar)
{
    x /= _scalar;
    y /= _scalar;
    z /= _scalar;
    w /= _scalar;

    return *this;
}

vector4 operator * (const double &_scalar, const vector4 &_other)
{
    return vector4(_scalar * _other.x, _scalar * _other.y,
        _scalar * _other.z, _scalar * _other.w);
}

matrix4x4::matrix4x4() {};

vector4 &matrix4x4::operator [] (const size_t &_index)
{
    return m_vectors[_index];
}

const vector4 &matrix4x4::operator [] (const size_t &_index) const
{
    return m_vectors[_index];
}

matrix4x4 matrix4x4::operator * (const matrix4x4 &_other) const
{
    matrix4x4 product;

    for(size_t i = 0; i < 4; ++i)
    {
        product[i].x = m_vectors[0].x * _other[i].x + m_vectors[1].x * _other[i].y
            + m_vectors[2].x * _other[i].z + m_vectors[3].x * _other[i].w;
        product[i].y = m_vectors[0].y * _other[i].x + m_vectors[1].y * _other[i].y
            + m_vectors[2].y * _other[i].z + m_vectors[3].y * _other[i].w;
        product[i].z = m_vectors[0].z * _other[i].x + m_vectors[1].z * _other[i].y
            + m_vectors[2].z * _other[i].z + m_vectors[3].z * _other[i].w;
        product[i].w = m_vectors[0].w * _other[i].x + m_vectors[1].w * _other[i].y
            + m_vectors[2].w * _other[i].z + m_vectors[3].w * _other[i].w;
    }

    return product;
}

vector4 matrix4x4::operator * (const vector4 &_other) const
{
    vector4 product;
    product.x = m_vectors[0].x * _other.x + m_vectors[1].x * _other.y
            + m_vectors[2].x * _other.z + m_vectors[3].x * _other.w;
    product.y = m_vectors[0].y * _other.x + m_vectors[1].y * _other.y
        + m_vectors[2].y * _other.z + m_vectors[3].y * _other.w;
    product.z = m_vectors[0].z * _other.x + m_vectors[1].z * _other.y
        + m_vectors[2].z * _other.z + m_vectors[3].z * _other.w;
    product.w = m_vectors[0].w * _other.x + m_vectors[1].w * _other.y
        + m_vectors[2].w * _other.z + m_vectors[3].w * _other.w;

    return product;
}

matrix4x4 &matrix4x4::operator *= (const matrix4x4 &_other)
{
    matrix4x4 product;

    for(size_t i = 0; i < 4; ++i)
    {
        product[i].x = m_vectors[0].x * _other[i].x + m_vectors[1].x * _other[i].y
            + m_vectors[2].x * _other[i].z + m_vectors[3].x * _other[i].w;
        product[i].y = m_vectors[0].y * _other[i].x + m_vectors[1].y * _other[i].y
            + m_vectors[2].y * _other[i].z + m_vectors[3].y * _other[i].w;
        product[i].z = m_vectors[0].z * _other[i].x + m_vectors[1].z * _other[i].y
            + m_vectors[2].z * _other[i].z + m_vectors[3].z * _other[i].w;
        product[i].w = m_vectors[0].w * _other[i].x + m_vectors[1].w * _other[i].y
            + m_vectors[2].w * _other[i].z + m_vectors[3].w * _other[i].w;
    }

    *this = product;

    return *this;
}