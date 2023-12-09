#ifndef SPHERE_COLLIDER_H
#define SPHERE_COLLIDER_H

#include <physics.hpp>

class sphere_collider : public collider
{
private:
    float m_radius;

public:
    sphere_collider(const float &radius = 1.0f);
    float &radius();
    const float &const_radius() const;
};

#endif