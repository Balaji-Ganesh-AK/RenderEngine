#version 330 core
    layout( location = 0 ) in vec4 v_Pos;
    layout( location = 1 ) in vec4 v_Color;
    layout( location = 2 ) in vec2 v_Texture;

    out vec4 f_Color;
    out vec2 f_Texture;
    uniform mat4 u_WorldProjection;
  
    void main()
    {
        f_Color = v_Color;
        f_Texture = v_Texture;
        gl_Position = u_WorldProjection * v_Pos ;
      
    }