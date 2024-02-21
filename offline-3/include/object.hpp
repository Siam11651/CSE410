#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <mesh.hpp>

class object
{
private:
    const mesh *m_object_mesh_ptr;

public:
    std::string name;
    bool active;
    transform object_transform;
    std::vector<object *> child_ptrs;

    object(const mesh *_object_mesh_ptr);
    object(const mesh *_object_mesh_ptr, const transform &_model_transform);
    void draw() const;
};

#endif