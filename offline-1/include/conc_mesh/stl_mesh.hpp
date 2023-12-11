#ifndef STL_MESH_H
#define STL_MESH_H

#include <mesh.hpp>
#include <string>

class stl_mesh : public mesh
{
public:
    stl_mesh(const std::string &file_path, const color &mesh_color);
};

#endif