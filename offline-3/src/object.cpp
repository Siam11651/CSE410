#include <object.hpp>
#include <GL/gl.h>
#include <cmath>

object::object()
{
    active = true;
}

object::object(const mesh &_object_mesh)
{
    active = true;
    object_mesh = _object_mesh;
}

object::object(const mesh &_object_mesh, const transform &_model_transform)
{
    active = true;
    object_mesh = object_mesh;
    object_transform = _model_transform;
}

void object::draw() const
{
    if(!active)
    {
        return;
    }

    constexpr float RAD2DEG = 180.0f / M_PI;
    const quaternion &rotation = object_transform.rotation;
    const float angle = rotation.get_angle();
    const vector3 axis = rotation.get_axis();
    const vector3 &position = object_transform.position;
    const vector3 &scale = object_transform.scale;

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(RAD2DEG * angle, axis.x, axis.y, axis.z);
    glScalef(scale.x, scale.y, scale.z);
    object_mesh.draw(object_transform);

    for(object *child : child_ptrs)
    {
        if(child)
        {
            child->draw();
        }
    }

    glPopMatrix();
}