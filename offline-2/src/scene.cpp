#include <scene.hpp>

view::view() :
    m_updated(false) {}

void view::set_eye(const vector4 &_eye)
{
    m_eye = _eye;
    m_updated = true;
}

const vector4 &view::get_eye() const
{
    return m_eye;
}

void view::set_look(const vector4 &_look)
{
    m_look = _look;
    m_updated = true;
}

const vector4 &view::get_look() const
{
    return m_look;
}

void view::set_up(const vector4 &_up)
{
    m_up = _up;
    m_updated = true;
}

const vector4 &view::get_up() const
{
    return m_up;
}

perspective::perspective() :
    m_updated(false) {}

void perspective::set_fov(const double &_fov)
{
    m_fov = _fov;
    m_updated = true;
}

const double &perspective::get_fov() const
{
    return m_fov;
}

void perspective::set_aspect_ratio(const double &_aspect_ratio)
{
    m_aspect_ratio = _aspect_ratio;
    m_updated = true;
}

const double &perspective::get_aspect_ratio() const
{
    return m_aspect_ratio;
}

void perspective::set_far(const double &_far)
{
    m_far = _far;
    m_updated = true;
}

const double &perspective::get_far() const
{
    return m_far;
}

void perspective::set_near(const double &_near)
{
    m_near = _near;
    m_updated = true;
}

const double &perspective::get_near() const
{
    return m_near;
}