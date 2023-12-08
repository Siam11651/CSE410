#ifndef BOX_MESH_H
#define BOX_MESH_H

#include <mesh.hpp>

class box_mesh : public mesh
{
public:
    box_mesh(const float &size_x = 1.0f, const float &size_y = 1.0f, const float &size_z = 1.0f);
};

#endif