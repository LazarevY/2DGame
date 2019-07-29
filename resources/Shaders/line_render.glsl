[vertex]
  #version 330 core
  layout (location = 0) in vec2 line;
  void main()
  {
    gl_Position = vec4(line, 0.0, 1.0);
  }
[/vertex]

[fragment]
  out vec4 color;
  void main()
  {
    color = vec4(1.0,0.0,0.0,1.0);
  }
[/fragment]
