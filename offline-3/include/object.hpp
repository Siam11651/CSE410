#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <mesh.hpp>

class object
{
public:
    std::string name;
    bool active;
    mesh object_mesh;
    transform object_transform;
    std::vector<object *> child_ptrs;

    object();
    object(const mesh &_object_mesh);
    object(const mesh &_object_mesh, const transform &_model_transform);
    void draw() const;
};

#endif