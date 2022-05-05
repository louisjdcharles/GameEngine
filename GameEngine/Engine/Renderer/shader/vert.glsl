#version 330 core
    
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Mvp;

void main()
{
    gl_Position = u_Mvp * vec4(position, 1);
    v_TexCoord = texCoord;
}