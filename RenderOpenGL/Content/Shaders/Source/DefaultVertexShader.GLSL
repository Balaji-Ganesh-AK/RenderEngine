#version 450 core
    layout( location = 0 ) in vec3 v_Pos;
    layout( location = 1 ) in vec2 v_Texture;
    layout( location = 2 ) in vec3 v_Normal;
    layout( location = 3 ) in float v_ID;
   

    out vec2 f_Texture;
    out vec3 f_Normal;
    out vec3 f_FragPos;
    out flat float f_ID;

    uniform mat4 u_WorldProjection;
    uniform mat4 u_Model;

    void main()
    {
      
        f_Texture = v_Texture;
        f_ID = v_ID;
   
        f_FragPos = vec3( u_Model * vec4( v_Pos, 1.0 ) );
        f_Normal =mat3(transpose(inverse(u_Model))) * v_Normal;
        gl_Position = u_WorldProjection * vec4(v_Pos, 1.0);
        
    }


##Shader End