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
    uniform vec3 triangle_colors[1];
    uniform float triangle_ambients[1];
    uniform float triangle_diffuses[1];
    uniform vec3 triangle_vertices[3];

    float circle_distance(vec3 center, vec3 source, vec3 ray)
    {
        vec3 _camera_pos = source - center;
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

    float triangle_distance(vec3 source, vec3 ray, int index)
    {
        vec3 v0 = triangle_vertices[index * 3];
        vec3 v1 = triangle_vertices[index * 3 + 1];
        vec3 v2 = triangle_vertices[index * 3 + 2];
        vec3 normal = normalize(cross(v1 - v0, v2 - v0));
        
        float D = -dot(normal, v0);
        float ray_dot = dot(normal, ray);

        if(abs(ray_dot) < 0.000001f)
        {
            return -8.0f;
        }

        float t = -(D + dot(source, normal)) / dot(normal, ray);

        if(t < 0.0f)
        {
            return -1.0f;
        }

        vec3 e1 = v1 - v0;
        vec3 e2 = v2 - v0;
        vec3 P = source + t * ray;
        float a = -1.0f;
        float b = -1.0f ;

        if(abs(e1.x * e2.y - e1.y * e2.x) >= 0.000001f && abs(e2.x * e1.y - e1.x * e2.y) >= 0.000001f)
        {
            a = (P.x * e2.y - P.y * e2.x) / (e1.x * e2.y - e1.y * e2.x);
            b = (P.x * e1.y - P.y * e1.x) / (e2.x * e1.y - e1.x * e2.y);
        }
        else if(abs(e1.y * e2.z - e1.z * e2.y) >= 0.000001f && abs(e2.y * e1.z - e1.y * e2.z) >= 0.000001f)
        {
            a = (P.y * e2.z - P.z * e2.y) / (e1.y * e2.z - e1.z * e2.y);
            b = (P.y * e1.z - P.z * e1.y) / (e2.y * e1.z - e1.y * e2.z);
        }
        else if(abs(e1.z * e2.x - e1.x * e2.z) >= 0.000001f && abs(e2.x * e1.x - e1.z * e2.x) >= 0.000001f)
        {
            a = (P.z * e2.x - P.x * e2.z) / (e1.z * e2.x - e1.x * e2.z);
            b = (P.z * e1.x - P.x * e1.z) / (e2.z * e1.x - e1.z * e2.x);
        }
        else
        {
            return -7.0f;
        }

        if(a < 0.0f)
        {
            return -2.0f;
        }

        if(a > 1.0f)
        {
            return -3.0f;
        }

        if(b < 0.0f)
        {
            return -4.0f;
        }

        if(b > 1.0f)
        {
            return -5.0f;
        }

        if(!(a + b <= 1.0f))
        {
            return -6.0f;
        }

        return t;
    }

    bool hit_other(float target_t, vec3 source, vec3 ray)
    {
        for(int j = 0; j < 2; ++j)
        {
            float t = circle_distance(circle_centers[j], source, ray);

            if(t < 0.0f)
            {
                continue;
            }

            if(t < target_t)
            {
                return false;
            }
        }

        for(int j = 0; j < 1; ++j)
        {
            float t = triangle_distance(source, ray, j);

            if(t < 0.0f)
            {
                continue;
            }

            if(t < target_t)
            {
                return false;
            }
        }

        return true;
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
        int min_object = -1;
        int min_circle_index = -1;
        int min_triangle_index = -1;

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
                min_object = 1;
            }
            else if(t < min_t)
            {
                min_t = t;
                min_circle_index = i;
                min_object = 1;
            }
        }

        for(int i = 0; i < 1; ++i)
        {
            float t = triangle_distance(camera_pos, ray, i);

            if(t < 0.0f)
            {
                continue;
            }

            if(min_t == -1)
            {
                min_t = t;
                min_triangle_index = i;
                min_object = 2;
            }
            else if(t < min_t)
            {
                min_t = t;
                min_triangle_index = i;
                min_object = 2;
            }
        }

        if(min_object == 1)
        {
            vec3 color = circle_colors[min_circle_index] * circle_ambients[min_circle_index];

            for(int i = 0; i < 1; ++i)
            {
                vec3 point = camera_pos + ray * min_t;
                vec3 light_ray = normalize(point - point_light_positions[i]);
                float target_t = circle_distance(circle_centers[min_circle_index], point_light_positions[i], light_ray);
                bool hit = hit_other(target_t, point_light_positions[i], light_ray);

                if(hit)
                {
                    vec3 normal = normalize(point - circle_centers[min_circle_index]);
                    float lambert = dot(normal, -light_ray);
                    vec3 c_color = circle_colors[min_circle_index] * max(lambert, 0);
                    color += point_light_colors[i] * circle_diffuses[min_circle_index] * c_color;
                }
            }

            frag_color = vec4(color, 1.0f);
        }
        else if(min_object == 2)
        {
            vec3 color = triangle_colors[min_triangle_index] * triangle_ambients[min_triangle_index];
            frag_color = vec4(color, 1.0f);
        }
    }
)";

#endif