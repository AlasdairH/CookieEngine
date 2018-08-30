#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 frag_texCoord;
out vec3 frag_vert;
out vec3 frag_normal;

uniform mat4 u_MVP;

void main()
{
	frag_texCoord = texCoord;
	frag_vert = position;
	frag_normal = normal;
    gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1.0);
}