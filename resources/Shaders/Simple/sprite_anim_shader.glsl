[vertex]
layout (location = 0) in vec2 vertexCoord;
layout (location = 1) in vec2 texCoord;

uniform mat3 normalize_vertexMatrix;


out vec2 TexCoord;

void main()
{
  vec3 temp = normalize_vertexMatrix * vec3(vertexCoord.xy,1.0);
  TexCoord =  texCoord;
  gl_Position = vec4(temp.x, -temp.y,0.0,1.0);
}
[/vertex]
[fragment]
#version 330 core

out vec4 color;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform mat3 normalize_textureMatrix;
uniform mat3 offset_matrix;

void main()
{
  vec3 texture_coord = normalize_textureMatrix * offset_matrix * vec3(TexCoord,1.0);
	vec4 temp = texture(ourTexture, vec2(texture_coord.xy));
	if(temp.a < 0.1)
		discard;
	color = temp;
}
[/fragment]
