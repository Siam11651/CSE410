#ifndef PHYSICS_H
#define PHYSICS_H

#include <cstdint>
#include <optional>
#include <space.hpp>

class object;

class collider
{

};

class collission_event
{
private:
    int64_t m_trigger_time;
    vector3 m_new_velocity;

public:
    collission_event(const int64_t &trigger_time, const vector3 &new_velocity);
    int64_t &trigger_time();
    vector3 &new_velocity();
    const int64_t &trigger_time() const;
    const vector3 &new_velocity() const;
    bool operator < (const collission_event &other) const;
};

class rigidbody
{
private:
    bool m_enabled;
    bool m_fixed;
    vector3 m_velocity;
    collider *m_collider;
    std::optional<collission_event> m_opt_collission_event;

public:
    rigidbody(collider *rb_collider);
    bool &enabled();
    const bool &const_enabled() const;
    bool &fixed();  // there is a keyword names static T_T
    const bool &const_fixed() const;
    vector3 &velocity();
    const vector3 &const_velocity() const;
    std::optional<collission_event> &opt_collission_event();
    const std::optional<collission_event> &const_opt_collission_event() const;
    void predict_collission(const collider *other_collider);
};

#endif