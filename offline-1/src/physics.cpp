#include <physics.hpp>
#include <object.hpp>
#include <exceptions.hpp>

collission_event::collission_event(const int64_t &trigger_time, const vector3 &new_velocity)
{
    m_trigger_time = trigger_time;
    m_new_velocity = new_velocity;
}

int64_t &collission_event::trigger_time()
{
    return m_trigger_time;
}

vector3 &collission_event::new_velocity()
{
    return m_new_velocity;
}

const int64_t &collission_event::trigger_time() const
{
    return m_trigger_time;
}

const vector3 &collission_event::new_velocity() const
{
    return m_new_velocity;
}

bool collission_event::operator < (const collission_event &other) const
{
    return m_trigger_time < other.m_trigger_time;
}

rigidbody::rigidbody(collider *rb_collider)
{
    if(rb_collider == nullptr)
    {
        throw null_collider_exception();
    }

    m_collider = rb_collider;
    m_enabled = true;
    m_fixed = false;
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

std::optional<collission_event> &rigidbody::opt_collission_event()
{
    return m_opt_collission_event;
}

const std::optional<collission_event> &rigidbody::const_opt_collission_event() const
{
    return m_opt_collission_event;
}

void rigidbody::predict_collission(const collider *other_collider)
{

}