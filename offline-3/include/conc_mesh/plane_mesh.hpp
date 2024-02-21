#ifndef PLANE_MESH_H
#define PLANE_MESH_H

#include <mesh.hpp>

class plane_mesh : public mesh
{
public:
    plane_mesh(const float &size_x, const float &size_z, const size_t &count_x, const size_t &count_z);
};

#endif