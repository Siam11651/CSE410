#include <space.hpp>
#include <cmath>

template <size_t N>
vector<N>::vector(const double &_x, const double &_y, const double &_z, const double &_w) :
    x(m_components[0]),
    y(m_components[1]),
    z(m_components[2]),
    w(m_components[3])
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

template <size_t N>
double vector<N>::get_magnitude() const
{
    double sum = 0.0;

    for(size_t i = 0; i < N; ++i)
    {
        sum += m_components[i] * m_components[i];
    }

    return std::sqrt(sum);
}

template <size_t N>
vector<N> vector<N>::get_normalized() const
{
    double m = get_magnitude();

    return vector<N>(x / m, y / m, z / m, w / m);
}

template <size_t N>
vector<N> &vector<N>::operator = (const vector<N> &_other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    w = _other.w;
}

template <size_t N>
vector<N> vector<N>::operator + (const vector<N> &_other) const
{
    return vector<N>(x + _other.x, y + _other.y, z + _other.z, w + _other.w);
}

template <size_t N>
vector<N> vector<N>::operator - (const vector<N> &_other) const
{
    return vector<N>(x - _other.x, y - _other.y, z - _other.z, w - _other.w);
}

template <size_t N>
vector<N> vector<N>::operator * (const double &_scalar) const
{
    return vector<N>(x * _scalar, y * _scalar, z * _scalar, w + _scalar);
}

template <size_t N>
vector<N> vector<N>::operator / (const double &_scalar) const
{
    return vector<N>(x / _scalar, y / _scalar, z / _scalar, w / _scalar);
}

template <size_t N>
vector<N> &vector<N>::operator += (const vector<N> &_other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    w += _other.w;

    return *this;
}

template <size_t N>
vector<N> &vector<N>::operator -= (const vector<N> &_other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    w -= _other.w;

    return *this;
}

template <size_t N>
vector<N> &vector<N>::operator *= (const double &_scalar)
{
    x *= _scalar;
    y *= _scalar;
    z *= _scalar;
    w *= _scalar;

    return *this;
}

template <size_t N>
vector<N> &vector<N>::operator /= (const double &_scalar)
{
    x /= _scalar;
    y /= _scalar;
    z /= _scalar;
    w /= _scalar;

    return *this;
}

template <size_t N>
vector<N> operator * (const double &_scalar, const vector<N> &_other)
{
    return vector<N>(_scalar * _other.x, _scalar * _other.y,
        _scalar * _other.z, _scalar * _other.w);
}

matrix4x4::matrix4x4() {};

vector<4> &matrix4x4::operator [] (const size_t &_index)
{
    return m_vectors[_index];
}

const vector<4> &matrix4x4::operator [] (const size_t &_index) const
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

vector<4> matrix4x4::operator * (const vector<4> &_other) const
{
    vector<4> product;
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