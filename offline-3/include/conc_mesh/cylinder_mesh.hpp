#ifndef CYLINDER_MESH_H
#define CYLINDER_MESH_H

#include <mesh.hpp>

class cylinder_mesh : public mesh
{
private:
    void constructor_helper(const float &radius, const float &height, const size_t &segments,
        const float &angle, const color &cylinder_color);

public:
    cylinder_mesh();
    cylinder_mesh(const float &radius, const float &height, const size_t &segments);
    cylinder_mesh(const float &radius, const float &height, const size_t &segments, const float &angle);
    cylinder_mesh(const float &radius, const float &height, const size_t &segments, const float &angle,
        const color &cylinder_color);
};

#endif