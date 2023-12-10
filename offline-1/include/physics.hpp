#ifndef PHYSICS_H
#define PHYSICS_H

#include <cstdint>
#include <optional>
#include <space.hpp>

class object;

class collission_event
{
private:
    int64_t m_trigger_time;
    vector3 m_new_velocity;

public:
    collission_event();
    collission_event(const int64_t &trigger_time, const vector3 &new_velocity);
    int64_t &trigger_time();
    const int64_t &const_trigger_time() const;
    vector3 &new_velocity();
    const vector3 &const_new_velocity() const;
    bool operator < (const collission_event &other) const;
};

class collider
{
private:
    object *m_parent_object;

public:
    collider();
    void set_parent_object(object *parent_object);
    object *get_parent_object() const;
    virtual collission_event *create_collission_event(collider *other_collider) = 0;
};

class rigidbody
{
private:
    bool m_enabled;
    bool m_fixed;
    vector3 m_velocity;
    object *m_parent_object;
    collission_event *m_collission_event;

public:
    rigidbody();
    bool &enabled();
    const bool &const_enabled() const;
    bool &fixed();  // there is a keyword names static T_T
    const bool &const_fixed() const;
    vector3 &velocity();
    const vector3 &const_velocity() const;
    void set_parent_object(object *parent_object);
    object *get_parent_object() const;
    collission_event *get_collission_event() const;
    void reset_collission_event();
    void predict_collission();
};

#endif