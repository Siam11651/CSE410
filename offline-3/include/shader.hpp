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
    uniform mat4 camera_transform;
    uniform vec3 bot_left;
    uniform float dx;
    uniform float dy;
    uniform vec3 point_light_positions[1];
    uniform vec3 point_light_colors[1];
    uniform vec3 circle_colors[2];
    uniform float circle_ambients[2];
    uniform float circle_diffuses[2];
    uniform vec3 circle_centers[2];

    float circle_distance(vec3 center, vec3 source, vec3 ray)
    {
        vec3 _camera_pos = camera_pos - center;
        float a = dot(ray, ray);
        float b = 2.0f * dot(ray, _camera_pos);
        float c = dot(_camera_pos, _camera_pos) - 0.5f;
        float discriminant = b * b - 4 * c * a;

        if(discriminant < 0.0f)
        {
            return -1.0f;
        }

        discriminant = sqrt(discriminant);
        float t_minus = (-b - discriminant) / (2.0f * a);
        float t = (-b + discriminant) / (2.0f * a);

        if(t < 0.0f)
        {
            return -1.0f;
        }

        if(t_minus >= 0.0f)
        {
            t = t_minus;
        }

        return t;
    }

    void main()
    {
        vec4 pixel = camera_transform * vec4(bot_left.x + gl_FragCoord.x / screen_dimension + dx, bot_left.y + gl_FragCoord.y / screen_dimension + dy, bot_left.z, 1.0f);
        float x = pixel.x;
        float y = pixel.y;
        float z = pixel.z;
        frag_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);
        vec3 ray = normalize(vec3(x, y, z) - camera_pos);
        float min_t = -1.0f;
        int min_circle_index = -1;

        for(int i = 0; i < 2; ++i)
        {
            float t = circle_distance(circle_centers[i], camera_pos, ray);

            if(t < 0.0f)
            {
                continue;
            }

            if(min_t < 0.0f)
            {
                min_t = t;
                min_circle_index = i;
            }
            else if(t < min_t)
            {
                min_t = t;
                min_circle_index = i;
            }
        }

        if(min_circle_index < 0)
        {
            return;
        }

        vec3 color = circle_colors[min_circle_index] * circle_ambients[min_circle_index];

        for(int i = 0; i < 1; ++i)
        {
            vec3 point = camera_pos + ray * min_t;
            vec3 light_ray = normalize(point - point_light_positions[i]);
            float target_t = length(point - point_light_positions[i]);
            bool hit = true;

            for(int j = 0; j < 2; ++j)
            {
                float t = circle_distance(circle_centers[j], point_light_positions[i], light_ray);

                if(t < 0.0f)
                {
                    continue;
                }

                if(t < target_t)
                {
                    hit = false;

                    break;
                }
            }

            if(hit)
            {
                vec3 normal = normalize(point - circle_centers[min_circle_index]);
                float lambert = dot(normal, -light_ray);
                vec3 c_color = circle_colors[min_circle_index] * lambert;
                color += point_light_colors[i] * circle_diffuses[min_circle_index] * c_color;
            }
        }

        frag_color = vec4(color, 1.0f);
    }
)";

#endif