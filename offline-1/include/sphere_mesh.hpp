#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include <mesh.hpp>
#include <cstdint>

class sphere_mesh : public mesh
{
private:
    float radius;
    uint64_t m_stack_count;
    uint64_t m_segment_count;

public:
    sphere_mesh(const float &radius, const uint64_t &stack_count, const uint64_t &segment_count);
};

#endif