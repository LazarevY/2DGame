[vertex]
#version 330 core

layout (location = 0) in vec2 vertexCoord;
layout (location = 1) in vec2 texCoord;

uniform mat3 normalize_vertexMatrix;
uniform mat3 normalize_textureMatrix;

out vec2 TexCoord;

void main()
{
  vec3 temp = normalize_vertexMatrix * vec3(vertexCoord.xy,1.0);
  vec3 texture_coord = normalize_textureMatrix * vec3(texCoord,1.0);
  TexCoord =  vec2(texture_coord.x, texture_coord.y);
  gl_Position = vec4(temp.x, -temp.y,0.0,1.0);
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
