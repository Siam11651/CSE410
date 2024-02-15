#ifndef SPACE_H
#define SPACE_H

#include <glm/glm.hpp>

class quaternion
{
public:
    float w;
    float x;
    float y;
    float z;

    quaternion();
    quaternion(const glm::vec3 &_euler_rotation);
    quaternion(const glm::vec3 &_axis, const float &_angle);
    quaternion(const float &_w, const float &_x, const float &_y, const float &_z);
    glm::vec3 get_axis() const;
    float get_angle() const;
    float get_magnitude() const;
    quaternion get_normalized() const;
    glm::vec3 get_rotated_vector(const glm::vec3 &source) const;
    quaternion operator * (const quaternion &other) const;
    static quaternion get_rotation(const glm::vec3 &from, const glm::vec3 &to);
};

class transform
{
public:
    glm::vec3 position;
    quaternion rotation;
    glm::vec3 scale;

    transform();
    transform(const glm::vec3 &_position);
    transform(const glm::vec3 &_position, const glm::vec3 &_euler_rotation);
    transform(const glm::vec3 &_position, const glm::vec3 &_euler_rotation, const glm::vec3 &_scale);
    glm::vec3 get_forward() const;
    glm::vec3 get_up() const;
    glm::vec3 get_left() const;
};

#endif