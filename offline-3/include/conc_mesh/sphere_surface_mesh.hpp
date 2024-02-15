#ifndef SPHERE_SURFACE_MESH_H
#define SPHERE_SURFACE_MESH_H

#include <mesh.hpp>

class sphere_surface_mesh : public mesh
{
private:
    void constructor_helper(const float &radius, const size_t &segments,
        const color &surface_color);

public:
    sphere_surface_mesh(const float &radius, const size_t &segments);
    sphere_surface_mesh(const float &radius, const size_t &segments,
        const color &surface_color);
};

#endif