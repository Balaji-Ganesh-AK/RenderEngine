#version 330 core
    layout( location = 0 ) in vec3 v_Pos;
  
    out vec3 f_FragPos;
    uniform mat4 u_WorldProjection;
    uniform mat4 u_Model;

    void main()
    {  
        f_FragPos = vec3( u_Model * vec4( v_Pos, 1.0 ) );
        gl_Position = u_WorldProjection * vec4(v_Pos, 1.0);
      
    }


##Shader End