#version 430 core

uniform sampler2D u_texture;
uniform vec4 u_diffuse = { 1.0f, 0.78f, 0.91f, 1.0f };
uniform bool u_useTexture = false;
uniform mat4 u_m;

layout(location = 0) out vec4 color;

in vec2 frag_texCoord;
in vec3 frag_vert;

void main()
{
	vec4 surfaceColor;
	if(u_useTexture)
	{
		surfaceColor = texture(u_texture, frag_texCoord);
	}
	else
	{
		surfaceColor = u_diffuse;
	}

    color = surfaceColor;
} 