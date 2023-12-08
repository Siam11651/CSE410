#ifndef MODEL_H
#define MODEL_H

#include <transform.hpp>
#include <mesh.hpp>

class model
{
private:
    const mesh *m_mesh;
    transform m_transform;

public:
    model(const mesh *model_mesh);
    model(const mesh *model_mesh, const transform &model_transform);
    transform &model_transform();
    const mesh *const_model_mesh() const;
    const transform &model_transform() const;
    void draw() const;
};

#endif