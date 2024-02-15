#ifndef SPACE_H
#define SPACE_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class transform
{
public:
    glm::vec3 position;
    glm::quat rotation;
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