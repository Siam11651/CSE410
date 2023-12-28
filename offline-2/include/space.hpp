#ifndef SPACE_H
#define SPACE_H

#include <cstddef>
#include <array>

template <size_t N>
class vector
{
private:
    std::array<double, 4> m_components;

public:
    double &x;
    double &y;
    double &z;
    double &w;

    vector<N>(const double &_x = 0.0, const double &_y = 0.0,
        const double &_z = 0.0, const double &_w = 0.0);
    vector<N>(const vector<N> &_other);
    double get_magnitude() const;
    vector<N> get_normalized() const;
    vector<N> &operator = (const vector<N> &_other);
    vector<N> operator + (const vector<N> &_other) const;
    vector<N> operator - (const vector<N> &_other) const;
    double operator * (const vector<N> &_other) const;
    vector<N> operator * (const double &_scalar) const;
    vector<N> operator / (const double &_scalar) const;
    vector<N> &operator += (const vector<N> &_other);
    vector<N> &operator -= (const vector<N> &_other);
    vector<N> &operator *= (const double &_scalar);
    vector<N> &operator /= (const double &_scalar);
    vector<N> operator - () const;
    template <size_t S>
    friend vector<S> operator * (const double &_scalar, const vector<S> &_other);
    friend vector<3> cross_product(const vector<3> &_a, const vector<3> &_b);
};

template class vector<2>;
template class vector<3>;
template class vector<4>;

class matrix4x4
{
private:
    std::array<vector<4>, 4> m_vectors;

public:
    matrix4x4();
    vector<4> &operator [] (const size_t &_index);
    const vector<4> &operator [] (const size_t &_index) const;
    matrix4x4 operator * (const matrix4x4 &_other) const;
    vector<4> operator * (const vector<4> &_other) const;
    matrix4x4 &operator *= (const matrix4x4 &_other);
    static matrix4x4 get_translation(const vector<3> &_source);
};

class quaternion
{
public:
    double w;
    double x;
    double y;
    double z;

    quaternion(const double &_w = 1.0, const double &_x = 0.0,
        const double &_y = 0.0, const double &_z = 0.0);
    quaternion(const vector<3> &_source, const vector<3> &_sink);
    double get_magnitude() const;
    quaternion get_normalized() const;
    matrix4x4 get_matrix() const;
    quaternion operator - () const;
};

class color
{
public:
    double r;
    double g;
    double b;
    double a;

    color();
    color(const double &_r, const double &_g, const double &_b);
    color(const double &_r, const double &_g, const double &_b, const double &_a);
    static color get_random_color();
};

#endif