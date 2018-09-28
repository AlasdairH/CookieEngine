#version 430 core

out vec4 fragColor;
  
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{ 
    fragColor = texture(screenTexture, texCoords);
	fragColor = vec4(1.0 - fragColor.r,1.0 -fragColor.g,1.0 -fragColor.b,1);
}