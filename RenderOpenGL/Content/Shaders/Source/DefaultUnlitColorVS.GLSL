#version 330 core
    layout( location = 0 ) in vec3 v_Pos;
    


    out vec3 f_FragPos;
    
    out vec4 f_Color;
    uniform mat4 u_WorldProjection;
    uniform mat4 u_Model;
    uniform vec4 u_Color;

    void main()
    {  
        f_FragPos = vec3( u_Model * vec4( v_Pos, 1.0 ) );
        
        gl_Position = u_WorldProjection * vec4(v_Pos, 1.0);
        f_Color= u_Color;
      
    }


##Shader End