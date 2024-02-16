#ifndef PYRAMID_MESH_H
#define PYRAMID_MESH_H

#include <mesh.hpp>

class pyramid_mesh : public mesh
{
public:
    pyramid_mesh(const float &_height, const float &_base_length, const float &_base_width, const color &_color);
};

#endif