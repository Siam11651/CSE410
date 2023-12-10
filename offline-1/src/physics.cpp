#include <physics.hpp>
#include <object.hpp>

collission_event::collission_event()
{
    m_trigger_time = INT64_MAX;
}

collission_event::collission_event(const int64_t &trigger_time, const vector3 &new_velocity)
{
    m_trigger_time = trigger_time;
    m_new_velocity = new_velocity;
}

int64_t &collission_event::trigger_time()
{
    return m_trigger_time;
}

const int64_t &collission_event::const_trigger_time() const
{
    return m_trigger_time;
}

vector3 &collission_event::new_velocity()
{
    return m_new_velocity;
}

const vector3 &collission_event::const_new_velocity() const
{
    return m_new_velocity;
}

bool collission_event::operator < (const collission_event &other) const
{
    return m_trigger_time < other.m_trigger_time;
}

collider::collider()
{
    m_parent_object = nullptr;
}

void collider::set_parent_object(object *parent_object)
{
    m_parent_object = parent_object;
}

object *collider::get_parent_object() const
{
    return m_parent_object;
}

rigidbody::rigidbody()
{
    m_enabled = true;
    m_fixed = false;
    m_parent_object = nullptr;
    m_collission_event = nullptr;
}

bool &rigidbody::enabled()
{
    return m_enabled;
}

const bool &rigidbody::const_enabled() const
{
    return m_enabled;
}

bool &rigidbody::fixed()
{
    return m_fixed;
}

const bool &rigidbody::const_fixed() const
{
    return m_fixed;
}

vector3 &rigidbody::velocity()
{
    return m_velocity;
}

const vector3 &rigidbody::const_velocity() const
{
    return m_velocity;
}

void rigidbody::set_parent_object(object *parent_object)
{
    m_parent_object = parent_object;
}

object *rigidbody::get_parent_object() const
{
    return m_parent_object;
}

void rigidbody::reset_collission_event()
{
    delete m_collission_event;

    m_collission_event = nullptr;
}

collission_event *rigidbody::get_collission_event() const
{
    return m_collission_event;
}