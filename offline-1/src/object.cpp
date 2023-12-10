#include <object.hpp>
#include <GL/gl.h>
#include <cmath>

object::object(const mesh &object_mesh)
{
    m_mesh = object_mesh;
    m_rigidbody = nullptr;
}

object::object(const mesh &object_mesh, const transform &model_transform)
{
    m_mesh = object_mesh;
    m_transform = model_transform;
    m_rigidbody = nullptr;
}

transform &object::object_transform()
{
    return m_transform;
}

const transform &object::const_object_transform() const
{
    return m_transform;
}

const mesh &object::const_object_mesh() const
{
    return m_mesh;
}

void object::set_rigidbody(rigidbody *object_rigidbody)
{
    m_rigidbody = object_rigidbody;

    if(m_rigidbody != nullptr)
    {
        m_rigidbody->set_parent_object(this);
    }
}

rigidbody *object::get_rigidbody() const
{
    return m_rigidbody;
}

void object::set_collider(collider *object_collider)
{
    m_collider = object_collider;

    if(m_collider != nullptr)
    {
        m_collider->set_parent_object(this);
    }
}

collider *object::get_collider() const
{
    return m_collider;
}

void object::draw() const
{
    constexpr float RAD2DEG = 180.0f / (float)M_PI;
    const quaternion &rotation = m_transform.const_rotation();
    const float angle = rotation.get_angle();
    const vector3 axis = rotation.get_axis();
    const vector3 &position = m_transform.const_position();
    const vector3 &scale = m_transform.const_scale();

    glPushMatrix();
    glTranslatef(-position.const_x(), position.const_y(), -position.const_z());
    glRotatef(RAD2DEG * angle, axis.const_x(), axis.const_y(), axis.const_z());
    glScalef(scale.const_x(), scale.const_y(), scale.const_z());
    m_mesh.draw();
    glPopMatrix();
}