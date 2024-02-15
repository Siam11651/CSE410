#include <conc_mesh/stl_mesh.hpp>
#include <fstream>
#include <cstdint>

void stl_mesh::constructor_helper(const std::string &file_path, const color &mesh_color)
{
    std::ifstream stl_ifstream(file_path);
    char stl_header[80];
    uint32_t face_count;

    stl_ifstream.read(stl_header, 80);
    stl_ifstream.read((char *)&face_count, 4);

    for(size_t i = 0; i < face_count; ++i)
    {
        std::array<vector3, 3> vertices;

        stl_ifstream.seekg(12, std::ios_base::cur);

        for(size_t i = 0; i < 3; ++i)
        {
            stl_ifstream.read((char *)&vertices[i].x, 4);
            stl_ifstream.read((char *)&vertices[i].y, 4);
            stl_ifstream.read((char *)&vertices[i].z, 4);
        }

        m_faces.emplace_back(vertices, mesh_color);
        stl_ifstream.seekg(2, std::ios_base::cur);
    }

    stl_ifstream.close();
}

stl_mesh::stl_mesh(const std::string &file_path)
{
    constructor_helper(file_path, color(1.0f, 1.0f, 1.0f, 1.0f));
}

stl_mesh::stl_mesh(const std::string &file_path, const color &mesh_color)
{
    constructor_helper(file_path, mesh_color);
}