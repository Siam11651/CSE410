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
    collider *m_collider;

public:
    object(const mesh &object_mesh);
    object(const mesh &object_mesh, const transform &model_transform);
    transform &object_transform();
    const transform &const_object_transform() const;
    const mesh &const_object_mesh() const;
    void set_rigidbody(rigidbody *object_rigidbody);
    rigidbody *get_rigidbody() const;
    void set_collider(collider *object_collider);
    collider *get_collider() const;
    void draw() const;
};

#endif