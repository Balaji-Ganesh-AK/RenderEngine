#version 330 core
    layout( location = 0 ) in vec3 v_Pos;
    layout( location = 1 ) in vec2 v_Texture;
   

    out vec2 f_Texture;
    out vec3 f_FragPos;
   
    void main()
    {
        f_Texture = v_Texture;
        f_FragPos = v_Pos;
  
        gl_Position =vec4(v_Pos, 1.0);
     
    }


##Shader End