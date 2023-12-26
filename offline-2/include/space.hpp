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
    double get_magnitude() const;
    vector<N> get_normalized() const;
    vector<N> &operator = (const vector<N> &_other);
    vector<N> operator + (const vector<N> &_other) const;
    vector<N> operator - (const vector<N> &_other) const;
    vector<N> operator * (const double &_scalar) const;
    vector<N> operator / (const double &_scalar) const;
    vector<N> &operator += (const vector<N> &_other);
    vector<N> &operator -= (const vector<N> &_other);
    vector<N> &operator *= (const double &_scalar);
    vector<N> &operator /= (const double &_scalar);
    friend vector<N> operator * (const double &_scalar, const vector<N> &_other);
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
};

#endif