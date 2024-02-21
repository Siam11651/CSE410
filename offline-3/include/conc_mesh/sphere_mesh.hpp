#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include <mesh.hpp>
#include <cstdint>

class sphere_mesh : public mesh
{
public:
    float radius;
    color sphere_color;

    sphere_mesh(const float &_radius, const size_t &stack_count, const size_t &segment_count, const color &_color);
};

#endif