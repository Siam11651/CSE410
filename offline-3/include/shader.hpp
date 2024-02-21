#ifndef SHADER_H
#define SHADER_H

const char *vertex_shader_source =
R"(
    #version 460 core

    layout (location = 0) in vec3 position;

    void main()
    {
        gl_Position = vec4(position.x, position.y, position.z, 1.0);
    }
)";

const char *fragment_shader_source =
R"(
    #version 460 core

    in vec4 gl_FragCoord;
    out vec4 frag_color;
    uniform int screen_dimension;
    uniform vec3 camera_pos;
    uniform vec3 bot_left;
    uniform float dx;
    uniform float dy;
    uniform vec3 centers[2];

    void main()
    {
        float x = bot_left.x + gl_FragCoord.x / screen_dimension + dx;
        float y = bot_left.y + gl_FragCoord.y / screen_dimension + dy;
        frag_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
        vec3 center = vec3(1.0f, 0.0f, 0.0f);
        vec3 ray = normalize(vec3(x, y, bot_left.z) - camera_pos);
        vec3 _camera_pos = camera_pos - center;
        float a = dot(ray, ray);
        float b = 2.0f * dot(ray, _camera_pos);
        float c = dot(_camera_pos, _camera_pos) - 0.5f;
        float discriminant = b * b - 4 * c * a;

        if(discriminant < 0.0f)
        {
            return;
        }

        frag_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
)";

#endif