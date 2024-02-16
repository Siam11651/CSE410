#include <conc_mesh/pyramid_mesh.hpp>

pyramid_mesh::pyramid_mesh(const float &_height, const float &_base_length, const float &_base_width, const color &_color) : mesh()
{
    m_faces.push_back(face(
    {
        glm::vec3(0.0f, _height, 0.0f),
        glm::vec3(-_base_width / 2.0f, 0.0f, _base_length / 2.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, _base_length / 2.0f)
    }, _color));
    m_faces.push_back(face(
    {
        glm::vec3(0.0f, _height, 0.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, _base_length / 2.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, -_base_length / 2.0f)
    }, _color));
    m_faces.push_back(face(
    {
        glm::vec3(0.0f, _height, 0.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, -_base_length / 2.0f),
        glm::vec3(-_base_width / 2.0f, 0.0f, -_base_length / 2.0f)
    }, _color));
    m_faces.push_back(face(
    {
        glm::vec3(0.0f, _height, 0.0f),
        glm::vec3(-_base_width / 2.0f, 0.0f, -_base_length / 2.0f),
        glm::vec3(-_base_width / 2.0f, 0.0f, _base_length / 2.0f)
    }, _color));
    m_faces.push_back(face(
    {
        glm::vec3(-_base_width / 2.0f, 0.0f, _base_length / 2.0f),
        glm::vec3(-_base_width / 2.0f, 0.0f, -_base_length / 2.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, _base_length / 2.0f)
    }, _color));
    m_faces.push_back(face(
    {
        glm::vec3(-_base_width / 2.0f, 0.0f, -_base_length / 2.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, -_base_length / 2.0f),
        glm::vec3(_base_width / 2.0f, 0.0f, _base_length / 2.0f)
    }, _color));
}