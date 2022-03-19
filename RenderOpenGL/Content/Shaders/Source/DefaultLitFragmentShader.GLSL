#version 330 core

    layout( location = 0 ) out vec4 color;
    struct Material
    {
        
        sampler2D Diffuse;
        sampler2D Specular;
        float Shininess;

 
    };

    struct FLight
    {
        int u_Light;
        vec3 u_LightDirection;
        vec3 Position;

       	float Constant;
		float Linear;		
		float Quadratic;
    };

    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;

    uniform vec4 u_LightColor;
    uniform vec4 u_ObjectColor;
  //  uniform vec3 u_LightPos;
    uniform vec3 u_CameraPos;
    

    uniform sampler2D u_Texture;
    uniform Material material;
    uniform FLight Light;
    
    void main()
    {
        //Attuenation calculation
        float distance = length(Light.Position - f_FragPos);
        float attenuation = 1.0/(Light.Constant + Light.Linear * distance + Light.Quadratic* (distance * distance));
           
            //Ambient
            float AmbientStrength =0.1f;
            //vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength * vec3( texture( material.Diffuse, f_Texture ) );
            vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength;
//            //Diffuse
//           
             vec3 Norm = normalize( f_Normal );
//
            vec3 LightDir = normalize(Light.u_LightDirection );

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
        
          vec3 result = ( Ambient*attenuation + Diffuse*attenuation + Specular*attenuation );
            //vec3 result = ( Ambient +Diffuse );

         //   color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) ;
           //  color =  vec4( result , 1.0) ;
           color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) * ( u_ObjectColor );
           // color =  vec4( result , 1.0)/* * ( u_ObjectColor )*/;
        
        
    }

##Shader End