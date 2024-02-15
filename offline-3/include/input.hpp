#ifndef INPUT_H
#define INPUT_H

#include <glm/glm.hpp>
#include <array>

class input
{
public:
    enum class key
    {
        mouse_left, mouse_right, key_w, key_a, key_s, key_d, key_up, key_down, key_left, key_right, key_q, key_e
    };

    enum class status
    {
        release, press, repeat
    };

    class mouse
    {
    private:
        glm::vec2 m_velocity;

    public:
        glm::vec2 position;

        mouse();
    };

private:
    static input::mouse s_mouse;
    static std::array<input::status, 12> s_key_status;

public:
    static void set_mouse(const input::mouse &_mouse);
    static const input::mouse &get_mouse();
    static void set_key(const input::key &_key, const input::status &_status);
    static const input::status &get_key(const input::key &_key);
};

#endif