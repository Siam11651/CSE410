#ifndef BOX_MESH_H
#define BOX_MESH_H

#include <mesh.hpp>

class box_mesh : public mesh
{
private:
    vector3 m_dimensions;

    void initialise_mesh(const vector3 &dimensions, const color &mesh_color);

public:
    box_mesh();
    box_mesh(const vector3 &dimensions);
    box_mesh(const vector3 &dimensions, const color &mesh_color);
    const vector3 &const_dimensions() const;
};

#endif