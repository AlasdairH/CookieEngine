#version 430 core

layout (std140) uniform u_camera_data
{ 
  mat4 viewMatrix;
  mat4 projectionMatrix;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 frag_texCoord;
out vec3 frag_vert;
out vec3 frag_normal;

uniform mat4 u_m;
uniform mat4 u_v;
uniform mat4 u_p;

void main()
{
	frag_texCoord = texCoord;
	frag_vert = position;
	frag_normal = normal;
	mat4 MVP = u_p * u_v * u_m;
    gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
}