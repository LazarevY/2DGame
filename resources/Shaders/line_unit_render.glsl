[vertex]
  #version 330 core
  layout (location = 0) in vec2 line;
  uniform mat3 stride;
  void main()
  {
    vec3 t_line = stride * vec3(line, 1.0);
    gl_Position = vec4(t_line.xy, 0.0, 1.0);
  }
[/vertex]

[fragment]
  out vec4 color;
  void main()
  {
    color = vec4(1.0,0.0,0.0,1.0);
  }
[/fragment]
