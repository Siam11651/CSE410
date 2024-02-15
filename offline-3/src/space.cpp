#include <space.hpp>
#include <cmath>
#include <array>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/quaternion.hpp>

transform::transform()
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

transform::transform(const glm::vec3 &_position)
{
    position = _position;
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

transform::transform(const glm::vec3 &_position, const glm::vec3 &_euler_rotation)
{
    position = _position;
    rotation = glm::quat(_euler_rotation);
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

transform::transform(const glm::vec3 &_position, const glm::vec3 &_euler_rotation, const glm::vec3 &_scale)
{
    position = _position;
    rotation = glm::quat(_euler_rotation);
    scale = _scale;
}

glm::vec3 transform::get_forward() const
{
    return glm::toMat4(rotation) * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

glm::vec3 transform::get_up() const
{
    return glm::toMat4(rotation) * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
}

glm::vec3 transform::get_left() const
{
    return glm::toMat4(rotation) * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
}