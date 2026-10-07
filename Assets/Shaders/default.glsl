#type vertex

#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;
out vec3 v_color;
out vec2 v_texCoord;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    v_color = a_Color;
    v_texCoord = a_TexCoord;
}

#type fragment
#version 460 core

in vec3 v_color;
in vec2 v_texCoord;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, v_texCoord); // * vec4(v_color, 1.0);
}
