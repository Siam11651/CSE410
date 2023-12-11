#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <mesh.hpp>
#include <physics.hpp>

class object
{
private:
    std::string m_name;
    bool m_active;
    mesh m_mesh;
    transform m_transform;
    rigidbody *m_rigidbody;
    collider *m_collider;

public:
    object(const mesh &object_mesh);
    object(const mesh &object_mesh, const transform &model_transform);
    std::string &name();
    const std::string &const_name() const;
    bool &active();
    const bool &const_active() const;
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