#version 330 core
    layout( location = 0 ) in vec3 v_Pos;
    layout( location = 1 ) in vec4 v_Color;


    out vec3 f_FragPos;
    out vec4 f_Color;
    uniform mat4 u_WorldProjection;
    uniform mat4 u_Model;

    void main()
    {  
        f_FragPos = vec3( u_Model * vec4( v_Pos, 1.0 ) );
        f_Color = v_Color;
        gl_Position = u_WorldProjection * vec4(v_Pos, 1.0);
      
    }


##Shader End