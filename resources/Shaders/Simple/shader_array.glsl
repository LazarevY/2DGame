[vertex]
#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
uniform mat3 normalize_vertexMatrix;
uniform mat3 transformMatrix;

void main()
{
  vec3 normalize_pos = normalize_vertexMatrix * transformMatrix * vec3(position,1.0);
  gl_Position = vec4(normalize_pos.x, normalize_pos.y, 0.0,1.0);
	TexCoord = texCoord;
}
[/vertex]
[fragment]
#version 330 core

out vec4 color;
in vec2 TexCoord;

uniform sampler2DArray ourTexture;
uniform int layer;
uniform bool inverse_x;
void main()
{
  vec2 texture_vector;
  texture_vector.x = TexCoord.x;
  texture_vector.y = 1 - TexCoord.y;
  if(inverse_x)
    texture_vector.x = 1 - TexCoord.x;

	vec4 temp = texture2DArray(ourTexture, vec3(texture_vector, layer));
	if(temp.a < 0.5)
		discard;
	color = temp;
}
[/fragment]
