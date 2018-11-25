#version 430 core

layout (std140) uniform u_camera_data
{ 
  mat4 viewMatrix;
  mat4 projectionMatrix;
  mat4 orthographicMatrix;
};

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec3 frag_vert;
out vec2 frag_texCoord;


uniform mat4 u_m;

void main()
{
	frag_vert = position;
	frag_texCoord = texCoord;

	mat4 MVP = orthographicMatrix * viewMatrix * u_m;
    gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
}