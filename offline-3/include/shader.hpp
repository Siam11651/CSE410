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
    uniform vec3 circle_colors[2];
    uniform vec3 centers[2];

    void main()
    {
        float x = bot_left.x + gl_FragCoord.x / screen_dimension + dx;
        float y = bot_left.y + gl_FragCoord.y / screen_dimension + dy;
        vec4 color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        float min_t = -1.0f;

        for(int i = 0; i < 2; ++i)
        {
            vec3 center = centers[i];
            vec3 ray = normalize(vec3(x, y, bot_left.z) - camera_pos);
            vec3 _camera_pos = camera_pos - center;
            float a = dot(ray, ray);
            float b = 2.0f * dot(ray, _camera_pos);
            float c = dot(_camera_pos, _camera_pos) - 0.5f;
            float discriminant = b * b - 4 * c * a;

            if(discriminant < 0.0f)
            {
                continue;
            }

            discriminant = sqrt(discriminant);
            float t_minus = (-b - discriminant) / (2.0f * a);
            float t = (-b + discriminant) / (2.0f * a);

            if(t_minus >= 0)
            {
                t = t_minus;
            }

            if(min_t < 0.0f)
            {
                min_t = t;
                color = vec4(circle_colors[i], 1.0f);
            }
            else if(t < min_t)
            {
                min_t = t;
                color = vec4(circle_colors[i], 1.0f);
            }
        }

        frag_color = color;
    }
)";

#endif