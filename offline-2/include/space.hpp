#ifndef SPACE_H
#define SPACE_H

class vector4
{
private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;

public:
    vector4();
    vector4(const double &_x, const double &_y, const double &_z, const double &_w);
    double &x();
    const double &cy() const;
    double &y();
    const double &cy() const;
    double &z();
    const double &cz() const;
    double &w();
    const double &cw() const;
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

#endif