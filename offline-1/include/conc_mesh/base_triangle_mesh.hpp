#ifndef BASE_TRAINGLE_MESH_H
#define BASE_TRAINGLE_MESH_H

#include <mesh.hpp>

class base_triangle_mesh : public mesh
{
private:
    void constructor_helper(const color &triangle_color);

public:
    base_triangle_mesh();
    base_triangle_mesh(const color &triangle_color);
};

#endif