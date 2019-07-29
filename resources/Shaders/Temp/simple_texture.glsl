[vertex]
  #version 330 core

  layout (location = 0) in vec4 mixed_coords;
  out vec2 texture_coord;

  uniform mat4 proj_view;
  uniform mat4 model;

  void main()
  {

    vec4 transform_vertex = proj_view * model * vec4(mixed_coords.xy, 0.0, 1.0);
    gl_Position = vec4(transform_vertex.xy, -1.0, 1.0);
    texture_coord = vec2(mixed_coords.zw);
  }
[/vertex]

[fragment]
  #version 330 core

  in vec2 texture_coord;
  out vec4 result_color;

  uniform sampler2D texture;

  void main()
  {
    vec4 color = texture(texture, vec2(texture_coord.x, 1 - texture_coord.y));
    if(color.a < 0.5)
      discard;
    result_color = color;
  }
[/fragment]
