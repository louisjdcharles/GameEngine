#version 330 core
    
layout(location = 0) out vec4 colour;

in vec4 gl_FragCoord;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Albedo;
uniform bool u_UsesTexture;

void main()
{
    if (u_UsesTexture) {
        colour = texture(u_Texture, v_TexCoord);
    } else {
        colour = u_Albedo;
    }
}