#include <object.hpp>
#include <GL/gl.h>
#include <cmath>

object::object(const mesh *_object_mesh_ptr)
{
    active = true;
    m_object_mesh_ptr = _object_mesh_ptr;
}

object::object(const mesh *_object_mesh_ptr, const transform &_model_transform)
{
    active = true;
    m_object_mesh_ptr = m_object_mesh_ptr;
    object_transform = _model_transform;
}

void object::draw() const
{
    if(!active)
    {
        return;
    }

    constexpr float RAD2DEG = 180.0f / M_PI;
    const glm::quat &rotation = object_transform.rotation;
    const float angle = glm::angle(rotation);
    const glm::vec3 axis = glm::axis(rotation);
    const glm::vec3 &position = object_transform.position;
    const glm::vec3 &scale = object_transform.scale;

    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(RAD2DEG * angle, axis.x, axis.y, axis.z);
    glScalef(scale.x, scale.y, scale.z);

    if(m_object_mesh_ptr)
    {
        m_object_mesh_ptr->draw(object_transform);
    }

    for(object *child : child_ptrs)
    {
        if(child)
        {
            child->draw();
        }
    }

    glPopMatrix();
}