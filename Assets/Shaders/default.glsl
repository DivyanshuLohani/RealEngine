#type vertex

#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;
out vec3 v_color;

void main()
{
    gl_Position = vec4(a_Position, 0.0, 1.0);
    v_color = a_Color;
}

#type fragment
#version 460 core

in vec3 v_color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(v_color, 1.0);
}
