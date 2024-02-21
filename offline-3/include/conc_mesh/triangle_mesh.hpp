#ifndef TRIANGLE_MESH_H
#define TRIANGLE_MESH_H

#include <mesh.hpp>

class triangle_mesh : public mesh
{
public:
    triangle_mesh(const face &_face);
};

#endif