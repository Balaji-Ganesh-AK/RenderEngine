#version 330 core
    layout( location = 0 ) in vec3 v_Pos;
    layout( location = 1 ) in vec2 v_Texture;
    layout( location = 2 ) in vec4 v_Color;
 

    out vec4 f_Color;
    out vec2 f_Texture;
    uniform mat4 u_WorldProjection;
  
    void main()
    {
       // f_Color = v_Color;
        f_Texture = v_Texture;
        gl_Position = u_WorldProjection * vec4(v_Pos, 1.0);
      
    }
##Shader End