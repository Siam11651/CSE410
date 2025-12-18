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
    uniform bool rtx_on;
    uniform bool lights_on;
    uniform uint screen_dimension;
    uniform vec3 camera_pos;
    uniform mat4 camera_transform;
    uniform vec3 bot_left;
    uniform float dx;
    uniform float dy;
    uniform uint level;
    uniform uint point_light_count;
    uniform vec3 point_light_positions[__1__];
    uniform vec3 point_light_colors[__1__];
    uniform uint spot_light_count;
    uniform vec3 spot_light_positions[__2__];
    uniform vec3 spot_light_directions[__2__];
    uniform vec3 spot_light_colors[__2__];
    uniform float spot_light_angles[__2__];
    float ground_dimension = 1000.0f;
    float ground_ambient = 0.5f;
    float ground_diffuse = 0.3f;
    float ground_specular = 0.25f;
    int ground_shininess = 50;
    float ground_reflection = 0.125f;
    uniform uint circle_count;
    uniform vec3 circle_colors[__3__];
    uniform float circle_ambients[__3__];
    uniform float circle_diffuses[__3__];
    uniform float circle_speculars[__3__];
    uniform uint circle_shininesses[__3__];
    uniform float circle_reflections[__3__];
    uniform vec3 circle_centers[__3__];
    uniform float circle_radius[__3__];
    uniform uint triangle_count;
    uniform vec3 triangle_colors[__4__];
    uniform float triangle_ambients[__4__];
    uniform float triangle_diffuses[__4__];
    uniform float triangle_speculars[__4__];
    uniform uint triangle_shininesses[__4__];
    uniform float triangle_reflections[__4__];
    uniform vec3 triangle_vertices0[__4__];
    uniform vec3 triangle_vertices1[__4__];
    uniform vec3 triangle_vertices2[__4__];
    uniform uint shape_count;
    uniform float shape_a[__5__];
    uniform float shape_b[__5__];
    uniform float shape_c[__5__];
    uniform float shape_d[__5__];
    uniform float shape_e[__5__];
    uniform float shape_f[__5__];
    uniform float shape_g[__5__];
    uniform float shape_h[__5__];
    uniform float shape_i[__5__];
    uniform float shape_j[__5__];
    uniform vec3 shape_colors[__5__];
    uniform float shape_ambients[__5__];
    uniform float shape_diffuses[__5__];
    uniform float shape_speculars[__5__];
    uniform uint shape_shininesses[__5__];
    uniform float shape_reflections[__5__];
    uniform vec3 shape_cube_positions[__5__];
    uniform vec3 shape_cube_dimensions[__5__];

    float circle_distance(vec3 center, vec3 source, vec3 ray, float radius)
    {
        vec3 _camera_pos = source - center;
        float a = dot(ray, ray);
        float b = 2.0f * dot(ray, _camera_pos);
        float c = dot(_camera_pos, _camera_pos) - radius * radius;
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
        vec3 v0 = triangle_vertices0[index];
        vec3 v1 = triangle_vertices1[index];
        vec3 v2 = triangle_vertices2[index];
        vec3 normal = normalize(cross(v2 - v0, v1 - v0));
        float D = -dot(normal, v0);
        float ray_dot = dot(normal, ray);

        if(abs(ray_dot) < 0.000001f)
        {
            return -1.0f;
        }

        float t = -(D + dot(source, normal)) / ray_dot;

        if(t < 0.0f)
        {
            return -2.0f;
        }

        vec3 e1 = v1 - v0;
        vec3 e2 = v2 - v0;
        vec3 P = source + t * ray - v0;
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
            return -3.0f;
        }

        if(a < 0.0f)
        {
            return -4.0f;
        }

        if(a > 1.0f)
        {
            return -5.0f;
        }

        if(b < 0.0f)
        {
            return -6.0f;
        }

        if(b > 1.0f)
        {
            return -7.0f;
        }

        if(!(a + b <= 1.0f))
        {
            return -8.0f;
        }

        return t;
    }

    float ground_distance(vec3 source, vec3 ray)
    {
        float half_dim = ground_dimension / 2.0f;
        vec3 v0 = vec3(-half_dim, 0.0f, -half_dim);
        vec3 v1 = vec3(-half_dim + ground_dimension, 0.0f, -half_dim);
        vec3 v2 = vec3(-half_dim, 0.0f, -half_dim + ground_dimension);
        vec3 normal = vec3(0.0f, 1.0f, 0.0f);
        float D = -dot(normal, v0);
        float ray_dot = dot(normal, ray);

        if(abs(ray_dot) < 0.0f)
        {
            return -1.0f;
        }

        float t = -(D + dot(source, normal)) / ray_dot;

        if(t < 0.0f)
        {
            return -2.0f;
        }

        vec3 P = source + t * ray - v0;
        
        if(P.x < 0.0f)
        {
            return -3.0f;
        }

        if(P.x >= ground_dimension)
        {
            return -4.0f;
        }

        if(P.z < 0.0f)
        {
            return -5.0f;
        }

        if(P.z >= ground_dimension)
        {
            return -6.0f;
        }

        return t;
    }

    float shape_distance(vec3 source, vec3 ray, int index)
    {
        float a = shape_a[index];
        float b = shape_b[index];
        float c = shape_c[index];
        float d = shape_d[index];
        float e = shape_e[index];
        float f = shape_f[index];
        float g = shape_g[index];
        float h = shape_h[index];
        float i = shape_i[index];
        float j = shape_j[index];
        float sx = source.x;
        float sy = source.y;
        float sz = source.z;
        float rx = ray.x;
        float ry = ray.y;
        float rz = ray.z;
        float _a = a * rx * rx + b * ry * ry + c * rz * rz + d * rx * ry + e * ry * rz + f * rz * rx;
        float _b = 2.0f * (a * sx * rx + b * sy * ry + c * sz * rz) + d * (sy * rx + sx * ry) + e * (sz * ry + sy * rz) + f * (sx * rz + sz * rx) + g * rx + h * ry + i * rz;
        float _c = a * sx * sx + b * sy * sy + c * sz * sz + d * sx * sy + e * sy * sz + f * sz * sx + g * sx + h * sy + i * sz + j;
        float _d = _b * _b - 4.0f * _c * _a;

        if(_d < 0.0f)
        {
            return -1.0f;
        }

        float min_t = (-_b - sqrt(_d)) / (2.0f * _a);
        float max_t = (-_b + sqrt(_b * _b - 4.0f * _a * _c)) / (2.0f * _a);
        float t[] = {min_t, max_t};

        for(int i = 0; i < 2; ++i)
        {
            if(t[i] < 0.01f)
            {
                continue;
            }

            vec3 point = source + t[i] * ray;

            if(shape_cube_dimensions[index].x > 0.0f)
            {
                if(shape_cube_positions[index].x - shape_cube_dimensions[index].x / 2.0f > point.x)
                {
                    continue;
                }

                if(point.x > shape_cube_positions[index].x + shape_cube_dimensions[index].x / 2.0f)
                {
                    continue;
                }
            }

            if(shape_cube_dimensions[index].y > 0.0f)
            {
                if(shape_cube_positions[index].y - shape_cube_dimensions[index].y / 2.0f > point.y)
                {
                    continue;
                }

                if(point.y > shape_cube_positions[index].y + shape_cube_dimensions[index].y / 2.0f)
                {
                    continue;
                }
            }

            if(shape_cube_dimensions[index].z > 0.0f)
            {
                if(shape_cube_positions[index].z - shape_cube_dimensions[index].z / 2.0f > point.z)
                {
                    continue;
                }

                if(point.z > shape_cube_positions[index].z + shape_cube_dimensions[index].z / 2.0f)
                {
                    continue;
                }
            }

            return t[i];
        }

        return -2.0f;
    }

    bool hit_other(float target_t, vec3 source, vec3 ray)
    {
        for(int j = 0; j < circle_count; ++j)
        {
            float t = circle_distance(circle_centers[j], source, ray, circle_radius[j]);

            if(t <= 0.01f)
            {
                continue;
            }

            if(t < target_t)
            {
                return false;
            }
        }

        for(int j = 0; j < triangle_count; ++j)
        {
            float t = triangle_distance(source, ray, j);

            if(t <= 0.01f)
            {
                continue;
            }

            if(t < target_t)
            {
                return false;
            }
        }

        {
            float t = ground_distance(source, ray);

            if(t > 0.01f && t < target_t)
            {
                return false;
            }
        }

        for(int j = 0; j < shape_count; ++j)
        {
            float t = shape_distance(source, ray, j);

            if(t <= 0.01f)
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
)"
R"(
    void main()
    {
        vec4 pixel = camera_transform * vec4(bot_left.x + gl_FragCoord.x / screen_dimension + dx, bot_left.y + gl_FragCoord.y / screen_dimension + dy, bot_left.z, 1.0f);
        float x = pixel.x;
        float y = pixel.y;
        float z = pixel.z;
        vec3 cam_pos = camera_pos;
        vec3 color = vec3(0.0f, 0.0f, 0.0f);
        vec3 ray = normalize(vec3(x, y, z) - camera_pos);
        float reflection_fraction = 1.0f;
        uint temp_level;

        if(rtx_on)
        {
            temp_level = level;
        }
        else
        {
            temp_level = 1;
        }

        for(int j = 0; j < temp_level; ++j)
        {
            float min_t = -1.0f;
            int min_object = -1;
            int min_circle_index = -1;
            int min_triangle_index = -1;
            int min_shape_index = -1;

            for(int i = 0; i < circle_count; ++i)
            {
                float t = circle_distance(circle_centers[i], cam_pos, ray, circle_radius[i]);

                if(t <= 0.01f)
                {
                    continue;
                }

                if(min_t == -1.0f)
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

            for(int i = 0; i < triangle_count; ++i)
            {
                float t = triangle_distance(cam_pos, ray, i);

                if(t <= 0.01f)
                {
                    continue;
                }

                if(min_t == -1.0f)
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

            {
                float t = ground_distance(cam_pos, ray);

                if(t > 0.01f)
                {
                    if(min_t == -1.0f)
                    {
                        min_t = t;
                        min_object = 3;
                    }
                    else if(t < min_t)
                    {
                        min_t = t;
                        min_object = 3;
                    }   
                }
            }

            for(int i = 0; i < shape_count; ++i)
            {
                float t = shape_distance(cam_pos, ray, i);

                if(t <= 0.01f)
                {
                    continue;
                }

                if(min_t == -1.0f)
                {
                    min_t = t;
                    min_shape_index = i;
                    min_object = 4;
                }
                else if(t < min_t)
                {
                    min_t = t;
                    min_shape_index = i;
                    min_object = 4;
                }
            }

            if(min_object == 1)
            {
                if(min_circle_index >= 0)
                {
                    color += circle_colors[min_circle_index] * circle_ambients[min_circle_index] * reflection_fraction;
                    vec3 point = cam_pos + ray * min_t;
                    vec3 normal = normalize(point - circle_centers[min_circle_index]);

                    for(int i = 0; lights_on && i < point_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - point_light_positions[i]);
                        float target_t = circle_distance(circle_centers[min_circle_index], point_light_positions[i], light_ray, circle_radius[min_circle_index]);
                        bool hit = hit_other(target_t, point_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, -light_ray);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), circle_shininesses[min_circle_index]);
                            vec3 c_color_diff = circle_colors[min_circle_index] * max(lambert, 0);
                            vec3 c_color_phong = circle_colors[min_circle_index] * phong;
                            color += point_light_colors[i] * circle_diffuses[min_circle_index] * c_color_diff * reflection_fraction;
                            color += point_light_colors[i] * circle_speculars[min_circle_index] * c_color_phong * reflection_fraction;
                        }
                    }

                    for(int i = 0; lights_on && i < spot_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - spot_light_positions[i]);
                        float dot_value = dot(light_ray, spot_light_directions[i]);
                        float angle = acos(dot_value);

                        if(angle > spot_light_angles[i])
                        {
                            continue;
                        }

                        float target_t = circle_distance(circle_centers[min_circle_index], spot_light_positions[i], light_ray, circle_radius[min_circle_index]);
                        bool hit = hit_other(target_t, spot_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, -light_ray);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), circle_shininesses[min_circle_index]);
                            vec3 c_color_diff = circle_colors[min_circle_index] * max(lambert, 0);
                            vec3 c_color_phong = circle_colors[min_circle_index] * phong;
                            color += spot_light_colors[i] * circle_diffuses[min_circle_index] * c_color_diff * reflection_fraction * dot_value;
                            color += spot_light_colors[i] * circle_speculars[min_circle_index] * c_color_phong * reflection_fraction * dot_value;
                        }
                    }

                    ray = ray + 2.0f * dot(-ray, normal) * normal;
                    cam_pos = point;
                    reflection_fraction *= circle_reflections[min_circle_index];
                }
                else
                {
                    break;
                }
            }
            else if(min_object == 2)
            {
                if(min_triangle_index >= 0)
                {
                    color += triangle_colors[min_triangle_index] * triangle_ambients[min_triangle_index] * reflection_fraction;
                    vec3 point = cam_pos + ray * min_t;
                    vec3 v0 = triangle_vertices0[min_triangle_index];
                    vec3 v1 = triangle_vertices1[min_triangle_index];
                    vec3 v2 = triangle_vertices2[min_triangle_index];
                    vec3 normal = normalize(cross(v2 - v0, v1 - v0));

                    for(int i = 0; lights_on && i < point_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - point_light_positions[i]);
                        float target_t = triangle_distance(point_light_positions[i], light_ray, min_triangle_index);
                        bool hit = hit_other(target_t, point_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, -light_ray);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), triangle_shininesses[min_triangle_index]);
                            vec3 c_color_diff = triangle_colors[min_triangle_index] * max(lambert, 0);
                            vec3 c_color_phong = triangle_colors[min_triangle_index] * phong;
                            color += point_light_colors[i] * triangle_diffuses[min_triangle_index] * c_color_diff * reflection_fraction;
                            color += point_light_colors[i] * triangle_speculars[min_triangle_index] * c_color_phong * reflection_fraction;
                        }
                    }

                    for(int i = 0; lights_on && i < spot_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - spot_light_positions[i]);
                        float dot_value = dot(light_ray, spot_light_directions[i]);
                        float angle = acos(dot_value);

                        if(angle > spot_light_angles[i])
                        {
                            continue;
                        }

                        float target_t = triangle_distance(spot_light_positions[i], light_ray, min_triangle_index);
                        bool hit = hit_other(target_t, spot_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, -light_ray);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), triangle_shininesses[min_triangle_index]);
                            vec3 c_color_diff = triangle_colors[min_triangle_index] * max(lambert, 0);
                            vec3 c_color_phong = triangle_colors[min_triangle_index] * phong;
                            color += spot_light_colors[i] * triangle_diffuses[min_triangle_index] * c_color_diff * reflection_fraction * dot_value;
                            color += spot_light_colors[i] * triangle_speculars[min_triangle_index] * c_color_phong * reflection_fraction * dot_value;
                        }
                    }

                    ray = ray + 2.0f * dot(-ray, normal) * normal;
                    cam_pos = point;
                    reflection_fraction *= triangle_reflections[min_triangle_index];
                }
                else
                {
                    break;
                }
            }
            else if(min_object == 3)
            {
                vec3 point = cam_pos + ray * min_t;
                vec3 v0 = vec3(-ground_dimension / 2.0f, 0.0f, -ground_dimension / 2.0f);
                vec3 P = point - v0;
                int x = int(P.x) / 20;
                int z = int(P.z) / 20;
                vec3 og_color;

                if(x % 2 == 0)
                {
                    if(z % 2 == 0)
                    {
                        og_color = vec3(1.0f, 1.0f, 1.0f);
                    }
                    else
                    {
                        og_color = vec3(0.0f, 0.0f, 0.0f);
                    }
                }
                else
                {
                    if(z % 2 == 0)
                    {
                        og_color = vec3(0.0f, 0.0f, 0.0f);
                    }
                    else
                    {
                        og_color = vec3(1.0f, 1.0f, 1.0f);
                    }
                }

                color += og_color * ground_ambient * reflection_fraction;
                vec3 normal = vec3(0.0f, 1.0f, 0.0f);

                for(int i = 0; lights_on && i < point_light_count; ++i)
                {
                    vec3 light_ray = normalize(point - point_light_positions[i]);
                    float target_t = ground_distance(point_light_positions[i], light_ray);
                    bool hit = hit_other(target_t, point_light_positions[i], light_ray);

                    if(hit)
                    {
                        vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                        float lambert = dot(normal, -light_ray);
                        float phong = pow(max(dot(reflection, -ray), 0.0f), ground_shininess);
                        vec3 c_color_diff = og_color * max(lambert, 0);
                        vec3 c_color_phong = og_color * phong;
                        color += point_light_colors[i] * ground_diffuse * c_color_diff * reflection_fraction;
                        color += point_light_colors[i] * ground_specular * c_color_phong * reflection_fraction;
                    }
                }

                for(int i = 0; lights_on && i < spot_light_count; ++i)
                {
                    vec3 light_ray = normalize(point - spot_light_positions[i]);
                    float dot_value = dot(light_ray, spot_light_directions[i]);
                    float angle = acos(dot_value);

                    if(angle > spot_light_angles[i])
                    {
                        continue;
                    }

                    float target_t = ground_distance(spot_light_positions[i], light_ray);
                    bool hit = hit_other(target_t, spot_light_positions[i], light_ray);

                    if(hit)
                    {
                        vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                        float lambert = dot(normal, -light_ray);
                        float phong = pow(max(dot(reflection, -ray), 0.0f), ground_shininess);
                        vec3 c_color_diff = og_color * max(lambert, 0);
                        vec3 c_color_phong = og_color * phong;
                        color += spot_light_colors[i] * ground_diffuse * c_color_diff * reflection_fraction * dot_value;
                        color += spot_light_colors[i] * ground_specular * c_color_phong * reflection_fraction * dot_value;
                    }
                }

                ray = ray + 2.0f * dot(-ray, normal) * normal;
                cam_pos = point;
                reflection_fraction *= ground_reflection;
            }
            else if(min_object == 4)
            {
                if(min_shape_index >= 0)
                {
                    color += shape_colors[min_shape_index] * shape_ambients[min_shape_index] * reflection_fraction;
                    vec3 point = cam_pos + ray * min_t;
                    float norm_x = 2.0f * shape_a[min_shape_index] * point.x + shape_d[min_shape_index] * point.y + shape_e[min_shape_index] * point.z;
                    float norm_y = 2.0f * shape_b[min_shape_index] * point.y + shape_d[min_shape_index] * point.x + shape_f[min_shape_index] * point.z;
                    float norm_z = 2.0f * shape_c[min_shape_index] * point.z + shape_e[min_shape_index] * point.x + shape_f[min_shape_index] * point.y;
                    vec3 normal = normalize(vec3(norm_x, norm_y, norm_z));

                    for(int i = 0; lights_on && i < point_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - point_light_positions[i]);
                        float target_t = shape_distance(point_light_positions[i], light_ray, min_shape_index);
                        bool hit = hit_other(target_t, point_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, reflection);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), shape_shininesses[min_shape_index]);
                            vec3 c_color_diff = shape_colors[min_shape_index] * max(lambert, 0);
                            vec3 c_color_phong = shape_colors[min_shape_index] * phong;
                            color += point_light_colors[i] * shape_diffuses[min_shape_index] * c_color_diff * reflection_fraction;
                            color += point_light_colors[i] * shape_speculars[min_shape_index] * c_color_phong * reflection_fraction;
                        }
                    }
)"
R"(
                    for(int i = 0; lights_on && i < spot_light_count; ++i)
                    {
                        vec3 light_ray = normalize(point - spot_light_positions[i]);
                        float dot_value = dot(light_ray, spot_light_directions[i]);
                        float angle = acos(dot_value);

                        if(angle > spot_light_angles[i])
                        {
                            continue;
                        }

                        float target_t = shape_distance(spot_light_positions[i], light_ray, min_shape_index);
                        bool hit = hit_other(target_t, spot_light_positions[i], light_ray);

                        if(hit)
                        {
                            vec3 reflection = light_ray + 2.0f * dot(-light_ray, normal) * normal;
                            float lambert = dot(normal, -light_ray);
                            float phong = pow(max(dot(reflection, -ray), 0.0f), shape_shininesses[min_shape_index]);
                            vec3 c_color_diff = shape_colors[min_shape_index] * max(lambert, 0);
                            vec3 c_color_phong = shape_colors[min_shape_index] * phong;
                            color += spot_light_colors[i] * shape_diffuses[min_shape_index] * c_color_diff * reflection_fraction * dot_value;
                            color += spot_light_colors[i] * shape_speculars[min_shape_index] * c_color_phong * reflection_fraction * dot_value;
                        }
                    }

                    ray = ray + 2.0f * dot(-ray, normal) * normal;
                    cam_pos = point;
                    reflection_fraction *= shape_reflections[min_shape_index];
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }

        frag_color = vec4(color, 1.0f);
    }
)";

#endif