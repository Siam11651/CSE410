#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include <physics.hpp>

class box_collider : public collider
{
private:
    vector3 m_dimensions;

public:
    box_collider(const vector3 &dimensions);
    vector3 &dimensions();
    const vector3 &const_dimensions() const;
    collission_event *create_collission_event(collider *other_collider);
};

#endif