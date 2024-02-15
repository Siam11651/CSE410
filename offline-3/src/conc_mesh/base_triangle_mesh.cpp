#include <conc_mesh/base_triangle_mesh.hpp>

void base_triangle_mesh::constructor_helper(const color &triangle_color)
{
    const std::array<glm::vec3, 3> face
    {
        glm::vec3(5.0f, 0.0f, 0.0f),
        glm::vec3(-0.5f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -10.0f)
    };

    m_faces.emplace_back(face, triangle_color);
}

base_triangle_mesh::base_triangle_mesh()
{
    constructor_helper(color(1.0f, 1.0f, 1.0f, 1.0f));
}

base_triangle_mesh::base_triangle_mesh(const color &triangle_color)
{
    constructor_helper(triangle_color);
}