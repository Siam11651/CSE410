#include <space.hpp>
#include <cmath>
#include <random>

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
vector<N>::vector(const vector<N> &_other) :
    x(m_components[0]),
    y(m_components[1]),
    z(m_components[2]),
    w(m_components[3])
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    w = _other.w;
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
    const double m = get_magnitude();

    return vector<N>(x / m, y / m, z / m, w / m);
}

template <size_t N>
vector<N> &vector<N>::operator = (const vector<N> &_other)
{
    x = _other.x;
    y = _other.y;
    z = _other.z;
    w = _other.w;

    return *this;
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
double vector<N>::operator * (const vector<N> &_other) const
{
    double sum = 0.0;

    for(size_t i = 0; i < N; ++i)
    {
        sum += m_components[i] * _other.m_components[i];
    }

    return sum;
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
vector<N> vector<N>::operator - () const
{
    vector<N> to_return;

    for(size_t i = 0; i < N; ++i)
    {
        to_return.m_components[i] = -m_components[i];
    }

    return to_return;
}

template <size_t N>
vector<N> operator * (const double &_scalar, const vector<N> &_other)
{
    return vector<N>(_scalar * _other.x, _scalar * _other.y,
        _scalar * _other.z, _scalar * _other.w);
}

vector<3> cross_product(const vector<3> &_a, const vector<3> &_b)
{
    vector<3> product;
    product.x = _a.y * _b.z - _a.z * _b.y;
    product.y = _a.z * _b.x - _a.x * _b.z;
    product.z = _a.x * _b.y - _a.y * _b.x;

    return product;
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

matrix4x4 matrix4x4::get_translation(const vector<3> &_source)
{
    matrix4x4 to_return;
    to_return[3].x = _source.x;
    to_return[3].y = _source.y;
    to_return[3].z = _source.z;
    to_return[0].x = 1.0;
    to_return[1].y = 1.0;
    to_return[2].z = 1.0;
    to_return[3].w = 1.0;

    return to_return;
}

quaternion::quaternion(const double &_w, const double &_x, const double &_y, const double &_z) :
    w(_w),
    x(_x),
    y(_y),
    z(_z) {}

quaternion::quaternion(const vector<3> &_source, const vector<3> &_sink)
{
    quaternion rotation;
    const vector<3> crossed = cross_product(_source, _sink);
    rotation.x = crossed.x;
    rotation.y = crossed.y;
    rotation.z = crossed.z;
    const double dotted = _source * _sink;
    const double source_magn_sqrd = std::pow(_source.get_magnitude(), 2.0);
    const double sink_magn_sqrd = std::pow(_sink.get_magnitude(), 2.0);
    rotation.w = dotted + std::sqrt(source_magn_sqrd * sink_magn_sqrd);

    if(rotation.w == 0.0)
    {
        rotation.x = 1.0;
        rotation.y = 0.0;
        rotation.z = 0.0;
    }

    *this = rotation.get_normalized();
}

double quaternion::get_magnitude() const
{
    return std::sqrt(w * w + x * x + y * y + z * z);
}

quaternion quaternion::get_normalized() const
{
    const double m = get_magnitude();

    return quaternion(w / m, x / m, y / m, z / m);
}

matrix4x4 quaternion::get_matrix() const
{
    matrix4x4 rotation;
    rotation[0].x = 1.0 - 2.0 * (y * y + z * z);
    rotation[1].x = 2.0 * (x * y - z * w);
    rotation[2].x = 2.0 * (x * z + y * w);
    rotation[0].y = 2.0 * (x * y + z * w);
    rotation[1].y = 1.0 - 2.0 * (x * x + z * z);
    rotation[2].y = 2.0 * (y * z - x * w);
    rotation[0].z = 2.0 * (x * z - y * w);
    rotation[1].z = 2.0 * (y * z + x * w);
    rotation[2].z = 1.0 - 2.0 * (x * x + y * y);
    rotation[3].w = 1.0;

    return rotation;
}

quaternion quaternion::operator - () const
{
    return quaternion(w, -x, -y, -z);
}

color::color() :
    r(0.0),
    g(0.0),
    b(0.0),
    a(1.0) {}

color::color(const double &_r, const double &_g, const double &_b) :
    r(_r),
    g(_g),
    b(_b),
    a(1.0) {}

color::color(const double &_r, const double &_g, const double &_b, const double &_a) :
    r(_r),
    g(_g),
    b(_b),
    a(_a) {}

color color::get_random_color()
{
    return color((double)std::random_device()() / std::random_device::max(),
        (double)std::random_device()() / std::random_device::max(),
        (double)std::random_device()() / std::random_device::max());
}