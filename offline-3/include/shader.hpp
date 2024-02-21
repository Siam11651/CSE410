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

    void main()
    {
        frag_color = vec4(gl_FragCoord.x / screen_dimension, 0.0f, gl_FragCoord.y / screen_dimension, 1.0f);
    }
)";

#endif