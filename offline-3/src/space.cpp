#include <space.hpp>
#include <cmath>
#include <array>

vector3 vector3::one(1.0f, 1.0f, 1.0f);

vector3::vector3(const float &_x, const float &_y, const float &_z)
{
    x = _x;
    y = _y;
    z = _z;
}

float vector3::get_magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

vector3 vector3::get_normalized() const
{
    float magnitude = get_magnitude();

    return vector3(x / magnitude, y / magnitude, z / magnitude);
}

bool vector3::operator == (const vector3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool vector3::operator != (const vector3 &other) const
{
    return !(x == other.x && y == other.y && z == other.z);
}

vector3 vector3::operator + (const vector3 &other) const
{
    return vector3(x + other.x, y + other.y, z + other.z);
}

vector3 &vector3::operator += (const vector3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

vector3 vector3::operator - (const vector3 &other) const
{
    return vector3(x - other.x, y - other.y, z - other.z);
}

vector3 &vector3::operator -= (const vector3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

vector3 vector3::operator * (const float &value) const
{
    return vector3(x * value, y * value, z * value);
}

vector3 &vector3::operator *= (const float &value)
{
    x *= value;
    y *= value;
    z *= value;

    return *this;
}

vector3 vector3::operator / (const float &value) const
{
    return vector3(x / value, y / value, z / value);
}

vector3 vector3::cross(const vector3 &vector_a, const vector3 &vector_b)
{
    return vector3(vector_a.y * vector_b.z - vector_a.z * vector_b.y, vector_a.z * vector_b.x - vector_a.x * vector_b.z, vector_a.x * vector_b.y - vector_a.y * vector_b.x);
}

float vector3::dot(const vector3 &vector_a, const vector3 &vector_b)
{
    return vector_a.x * vector_b.x + vector_a.y * vector_b.y + vector_a.z * vector_b.z;
}

quaternion::quaternion()
{
    w = 1.0f;
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

quaternion::quaternion(const vector3 &_euler_rotation)
{
    const float &ex = _euler_rotation.x;
    const float &ey = _euler_rotation.y;
    const float &ez = _euler_rotation.z;
    quaternion qx(std::cos(ex / 2.0f), std::sin(ex / 2.0f), 0.0f, 0.0f);
    quaternion qy(std::cos(ey / 2.0f), 0.0f, std::sin(ey / 2.0f), 0.0f);
    quaternion qz(std::cos(ez / 2.0f), 0.0f, 0.0f, std::sin(ez / 2.0f));
    quaternion new_q = qz * qy * qx;
    w = new_q.w;
    x = new_q.x;
    y = new_q.y;
    z = new_q.z;
}

quaternion::quaternion(const vector3 &_axis, const float &_angle)
{
    w = std::cos(_angle / 2.0f);
    x = _axis.x * std::sin(_angle / 2.0f);
    y = _axis.y * std::sin(_angle / 2.0f);
    z = _axis.z * std::sin(_angle / 2.0f);
}

quaternion::quaternion(const float &_w, const float &_x, const float &_y, const float &_z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}

vector3 quaternion::get_axis() const
{
    const float angle = std::acos(w);

    if(angle == 0.0f)
    {
        return vector3(0.0f, 0.0f, 0.0f);
    }

    const float new_x = x / std::sin(angle);
    const float new_y = y / std::sin(angle);
    const float new_z = z / std::sin(angle);

    return vector3(new_x, new_y, new_z);
}

quaternion quaternion::get_normalized() const
{
    const float magnitude = get_magnitude();

    return quaternion(w / magnitude, x / magnitude, y / magnitude, z / magnitude);
}

float quaternion::get_angle() const
{
    return std::acos(w) * 2.0f;
}

float quaternion::get_magnitude() const
{
    return std::sqrt(w * w + x * x + y * y + z * z);
}

vector3 quaternion::get_rotated_vector(const vector3 &source) const
{
    std::array<std::array<float, 3>, 3> matrix
    {
        std::array<float, 3>
        {
            1.0f - 2.0f * (y * y + z * z),
            2.0f * (x * y - w * z),
            2.0f * (x * z + w * y)
        },
        std::array<float, 3>
        {
            2.0f * (x * y + w * z),
            1.0f - 2.0f * (x * x + z * z),
            2.0f * (y * z - w * x)
        },
        std::array<float, 3>
        {
            2.0f * (x * z - w * y),
            2.0f * (y * z + w * x),
            1.0f - 2.0f * (x * x + y * y)
        }
    };

    const float &sx = source.x;
    const float &sy = source.y;
    const float &sz = source.z;

    return vector3(sx * matrix[0][0] + sy * matrix[0][1] + sz * matrix[0][2], sx * matrix[1][0] + sy * matrix[1][1] + sz * matrix[1][2], sx * matrix[2][0] + sy * matrix[2][1] + sz * matrix[2][2]);
}

quaternion quaternion::operator * (const quaternion &other) const
{
    const quaternion &q1 = *this;
    const quaternion &q2 = other;
    float new_w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    float new_x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    float new_y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    float new_z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

    return quaternion(new_w, new_x, new_y, new_z);
}

quaternion quaternion::get_rotation(const vector3 &from, const vector3 &to)
{
    const vector3 cross_product = vector3::cross(from, to);
    const float from_magn_2 = std::pow(from.get_magnitude(), 2.0f);
    const float to_magn_2 = std::pow(to.get_magnitude(), 2.0f);;
    const float qw = std::sqrt(from_magn_2 * to_magn_2) + vector3::dot(from, to);
    float qx = cross_product.x;
    float qy = cross_product.y;
    float qz = cross_product.z;

    if(qw == 0.0f)
    {
        qx = 0.0f;
        qy = 1.0f;
        qz = 0.0f;
    }

    return quaternion(qw, qx, qy, qz).get_normalized();
}

transform::transform()
{
    scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &_position)
{
    position = _position;
    scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &_position, const vector3 &_euler_rotation)
{
    position = _position;
    rotation = quaternion(_euler_rotation);
    scale = vector3(1.0f, 1.0f, 1.0f);
}

transform::transform(const vector3 &_position, const vector3 &_euler_rotation, const vector3 &_scale)
{
    position = _position;
    rotation = quaternion(_euler_rotation);
    scale = _scale;
}

vector3 transform::get_forward() const
{
    return rotation.get_rotated_vector(vector3(0.0f, 0.0f, 1.0f));
}

vector3 transform::get_up() const
{
    return rotation.get_rotated_vector(vector3(0.0f, 1.0f, 0.0f));
}

vector3 transform::get_left() const
{
    return rotation.get_rotated_vector(vector3(1.0f, 0.0f, 0.0f));
}