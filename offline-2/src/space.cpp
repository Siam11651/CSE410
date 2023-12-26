#include <space.hpp>

vector4::vector4() :
    m_x(0.0),
    m_y(0.0),
    m_z(0.0),
    m_w(0.0) {}

vector4::vector4(const double &_x, const double &_y, const double &_z, const double &_w) :
    m_x(_x),
    m_y(_y),
    m_z(_z),
    m_w(_w) {}

double &vector4::x()
{
    return m_x;
}

const double &vector4::cy() const
{
    return m_x;
}

double &vector4::y()
{
    return m_y;
}

const double &vector4::cy() const
{
    return m_y;
}

double &vector4::z()
{
    return m_z;
}

const double &vector4::cz() const
{
    return m_z;
}

double &vector4::w()
{
    return m_w;
}

const double &vector4::cw() const
{
    return m_w;
}

vector4 vector4::operator + (const vector4 &_other) const
{
    return vector4(m_x + _other.m_x, m_y + _other.m_y, m_z + _other.m_z, m_w + _other.m_w);
}

vector4 vector4::operator - (const vector4 &_other) const
{
    return vector4(m_x - _other.m_x, m_y - _other.m_y, m_z - _other.m_z, m_w - _other.m_w);
}

vector4 vector4::operator * (const double &_scalar) const
{
    return vector4(m_x * _scalar, m_y * _scalar, m_z * _scalar, m_w * _scalar);
}

vector4 vector4::operator / (const double &_scalar) const
{
    return vector4(m_x / _scalar, m_y / _scalar, m_z / _scalar, m_w / _scalar);
}

vector4 &vector4::operator += (const vector4 &_other)
{
    m_x += _other.m_x;
    m_y += _other.m_y;
    m_z += _other.m_z;
    m_w += _other.m_w;

    return *this;
}

vector4 &vector4::operator -= (const vector4 &_other)
{
    m_x -= _other.m_x;
    m_y -= _other.m_y;
    m_z -= _other.m_z;
    m_w -= _other.m_w;

    return *this;
}

vector4 &vector4::operator *= (const double &_scalar)
{
    m_x *= _scalar;
    m_y *= _scalar;
    m_z *= _scalar;
    m_w *= _scalar;

    return *this;
}

vector4 &vector4::operator /= (const double &_scalar)
{
    m_x /= _scalar;
    m_y /= _scalar;
    m_z /= _scalar;
    m_w /= _scalar;

    return *this;
}

vector4 operator * (const double &_scalar, const vector4 &_other)
{
    return vector4(_scalar * _other.m_x, _scalar * _other.m_y,
        _scalar * _other.m_z, _scalar * _other.m_w);
}