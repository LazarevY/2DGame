[vertex]
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

void main()
{
  gl_Position = vec4(position.x, -position.y, 0.0,1.0);
	TexCoord = texCoord;
}
[/vertex]
[fragment]
#version 330 core

out vec4 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
void main()
{
	vec4 temp = texture(ourTexture, TexCoord);
	if(temp.a < 0.1)
		discard;
	color = temp;
}
[/fragment]
