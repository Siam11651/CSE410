#include <conc_mesh/base_triangle_mesh.hpp>

void base_triangle_mesh::constructor_util(const color &triangle_color)
{
    const std::array<vector3, 3> face
    {
        vector3(1.0f, 0.0f, 0.0f),
        vector3(0.0f, 1.0f, 0.0f),
        vector3(0.0f, 0.0f, 1.0f)
    };

    m_faces.emplace_back(face, triangle_color);
}

base_triangle_mesh::base_triangle_mesh()
{
    constructor_util(color(1.0f, 1.0f, 1.0f, 1.0f));
}

base_triangle_mesh::base_triangle_mesh(const color &triangle_color)
{
    constructor_util(triangle_color);
}