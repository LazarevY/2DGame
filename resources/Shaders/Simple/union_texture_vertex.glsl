[vertex]
  #version 330 core
  layout (location = 0) in vec2 vertexCoord;
  out vec3 textCoord;
  uniform mat3 normalize_vertexMatrix;
  uniform mat3 normalize_textureMatrix;
  uniform mat3 transformMatrix;

  void main()
  {
    textCoord = normalize_textureMatrix * vec3(vertexCoord, 1.0);
    vec3 out_vec = normalize_vertexMatrix * transformMatrix * vec3(vertexCoord, 1.0);
    gl_Position = vec4(out_vec.x, out_vec.y, 0.0, 1.0);
  }
[/vertex]
[fragment]
  #version 330 core
  out vec4 color;
  in vec3 textCoord;

  uniform sampler2D ourTexture;
  void main()
  {
  	vec4 temp = texture(ourTexture, vec2(textCoord.x, 1 - textCoord.y));
  	if(temp.a < 0.1)
  		discard;
  	color = temp;
  }
[/fragment]
