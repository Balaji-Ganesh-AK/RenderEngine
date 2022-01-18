#version 330 core

    layout( location = 0 ) out vec4 color;
    struct Material
    {
        vec3 Ambient;
        vec3 Diffuse;
        vec3 Specular;
        float Shininess;
    };
    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;

    uniform vec4 u_LightColor;
    uniform vec4 u_ObjectColor;
    uniform vec3 u_LightPos;
    uniform vec3 u_CameraPos;
    uniform sampler2D u_Texture;
    uniform int u_Light;

    uniform Material material;
    
    void main()
    {
        
        if ( u_Light == 0 )
        {
            color = texture( u_Texture, f_Texture ) * vec4( u_ObjectColor );
        }
        else
        {
            //Ambient
            vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * material.Ambient;

            //Diffuse
           
            vec3 Norm = normalize( f_Normal );

            vec3 LightDir = normalize( u_LightPos - f_FragPos );
            float DiffuseStrength = max( dot( Norm, LightDir ),0.0 );
            vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength * material.Diffuse );

            //Specular 
            vec3 ViewDir = normalize( u_CameraPos - f_FragPos );
            vec3 ReflectDir = reflect( -LightDir, Norm );
            float SpecularStrength = pow( max( dot( ViewDir, ReflectDir ), 0.0 ), material.Shininess );
            vec3 Specular = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *( SpecularStrength * material.Specular);

      
        //    
        
            vec3 result = ( Diffuse + Ambient + Specular );


           color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) * ( u_ObjectColor );
        }
        //
    }