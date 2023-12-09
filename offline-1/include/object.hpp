#ifndef OBJECT_H
#define OBJECT_H

#include <optional>
#include <mesh.hpp>
#include <physics.hpp>

class object
{
private:
    mesh m_mesh;
    transform m_transform;
    rigidbody *m_rigidbody;

public:
    object(const mesh &object_mesh);
    object(const mesh &object_mesh, const transform &model_transform);
    transform &object_transform();
    const transform &const_object_transform() const;
    const mesh &const_object_mesh() const;
    void set_rigidbody(rigidbody *object_rigidbody);
    rigidbody *get_rigidbody() const;
    void draw() const;
};

#endif