#include <input.hpp>

input::mouse input::s_mouse;
std::array<input::status, 12> input::s_key_status;

input::mouse::mouse() {}

void input::input::set_mouse(const input::mouse &_mouse)
{
    s_mouse = _mouse;
}

const input::mouse &input::input::get_mouse()
{
    return s_mouse;
}

void input::set_key(const input::key &_key, const input::status &_status)
{
    s_key_status[(size_t)_key] = _status;
}

const input::status &input::get_key(const input::key &_key)
{
    return s_key_status[(size_t)_key];
}