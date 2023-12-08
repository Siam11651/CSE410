#include <model.hpp>
#include <GL/gl.h>
#include <cmath>

model::model(const mesh *model_mesh)
{
    m_mesh = model_mesh;
}

model::model(const mesh *model_mesh, const transform &model_transform)
{
    m_mesh = model_mesh;
    m_transform = model_transform;
}

transform &model::model_transform()
{
    return m_transform;
}

const mesh *model::const_model_mesh() const
{
    return m_mesh;
}

const transform &model::model_transform() const
{
    return m_transform;
}

void model::draw() const
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
    m_mesh->draw();
    glPopMatrix();
}