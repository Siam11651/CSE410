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

    void main()
    {
        float x = bot_left.x + gl_FragCoord.x / screen_dimension + dx + 0.5f;
        float y = bot_left.y + gl_FragCoord.y / screen_dimension + dy + 0.5f;
        frag_color = vec4(x, y, 0.0f, 1.0f);
    }
)";

#endif