#version 330 core

    layout( location = 0 ) out vec4 color;
    struct Material
    {
        
        sampler2D Diffuse;
        sampler2D Specular;
        float Shininess;
    };
    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;

    uniform vec4 u_LightColor;
    uniform vec4 u_ObjectColor;
    uniform vec3 u_LightPos;
    uniform vec3 u_CameraPos;
    
    uniform int u_Light;
    uniform sampler2D u_Texture;
    uniform Material material;
    
    void main()
    {
        
        if ( u_Light == 0 )
        {
            color =texture( u_Texture, f_Texture ) * vec4( u_ObjectColor );
        }
        else
        {
           // color = texture( material.Ambient, f_Texture ) * vec4( u_ObjectColor );
            //Ambient
            float AmbientStrength =0.1f;
            //vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength * vec3( texture( material.Diffuse, f_Texture ) );
            vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength;
//            //Diffuse
//           
             vec3 Norm = normalize( f_Normal );
//
            vec3 LightDir = normalize( u_LightPos - f_FragPos );
            float DiffuseStrength = max( dot( Norm, LightDir ),0.0 );
             vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength);
            //vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength * vec3(texture(material.Diffuse, f_Texture )));

            //Specular 
            vec3 ViewDir = normalize(u_CameraPos - (f_FragPos ));
            vec3 ReflectDir = reflect( -LightDir, Norm );
            float SpecularStrength = pow( max( dot( ViewDir, ReflectDir ), 0.0 ), material.Shininess );
//          //  vec3 Specular = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *( SpecularStrength * vec3( texture( material.Specular, f_Texture ) ) );
           vec3 Specular = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *( SpecularStrength  );

      
        //    
        
          vec3 result = ( Ambient +Diffuse+Specular );
            //vec3 result = ( Ambient +Diffuse );

         //   color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) ;
           //  color =  vec4( result , 1.0) ;
           color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) * ( u_ObjectColor );
           // color =  vec4( result , 1.0)/* * ( u_ObjectColor )*/;
        }
        
    }

##Shader End