#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include <mesh.hpp>
#include <cstdint>

class sphere_mesh : public mesh
{
public:
    sphere_mesh(const float &radius, const size_t &stack_count, const size_t &segment_count);
};

#endif