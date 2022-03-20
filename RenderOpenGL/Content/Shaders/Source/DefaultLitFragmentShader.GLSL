#version 330 core

    layout( location = 0 ) out vec4 color;
     #define MAX_POINTLIGHTS 100
    struct FMaterial
    {
        
        sampler2D Diffuse;
        sampler2D Specular;
        float Shininess;

 
    };

    struct FDirectionalLight
    {
        vec3 Direction;

        vec3 Ambient;
        vec3 Diffuse;
        vec3 Specular;
    };

    struct FPointLight
    {
        vec3 Position;

        float Constant;
		float Linear;		
		float Quadratic;

        vec3 Ambient;
        vec3 Diffuse;
        vec3 Specular;

    };

    struct FSpotLight
    {
        vec3 Direction;
        vec3 Position;

       	float Constant;
		float Linear;		
		float Quadratic;

        float CutOff;
        float OuterCutOff;
    };
    struct FLight
    {
        int u_Light;
        vec3 u_LightDirection;
        vec3 Position;

       	float Constant;
		float Linear;		
		float Quadratic;

        float CutOff;
        float OuterCutOff;
    };

    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;

    uniform vec4 u_LightColor;
    uniform vec4 u_ObjectColor;
  //  uniform vec3 u_LightPos;
    uniform vec3 CameraPosition;
    uniform vec3 CameraFront;
    

    uniform sampler2D u_Texture;
    uniform FMaterial Material;
  
    uniform FDirectionalLight DirectionalLight;
    uniform FPointLight PointLights[MAX_POINTLIGHTS];
    uniform int CurrentPointLightCount = 0;
    //Function Prototypes
    vec3 CalulateDirectionLight(FDirectionalLight DirectionLight, vec3 Normal, vec3 ViewDirection, FMaterial material);
    vec3 CalulatePointLight(FPointLight PointLight, vec3 Normal, vec3 ViewDirection, FMaterial material, vec3 FragPosition);

    void main()
    {

    vec3 ViewDirection = normalize((CameraFront) - (f_FragPos ));
        vec3 Normal = normalize(f_Normal);
      vec3 Result;
        Result += CalulateDirectionLight(DirectionalLight, Normal,ViewDirection,Material);
        for(int i =0;i< CurrentPointLightCount; i++)
        {
            Result += CalulatePointLight(PointLights[i], Normal, ViewDirection,Material,f_FragPos);
        }


        color =   vec4(Result, 1.0);



//        //Attuenation calculation
//        float distance = length(Light.Position - f_FragPos);
//        float attenuation = 1.0/(Light.Constant + Light.Linear * distance + Light.Quadratic* (distance * distance));
//        vec3 LightDir = normalize(Light.Position - f_FragPos);
//        float theta = dot(LightDir, normalize(-Light.u_LightDirection));
//        float epsilon = Light.CutOff - Light.OuterCutOff;
//        float intensity = clamp((theta - Light.OuterCutOff)/ epsilon, 0.0, 1.0);
//
//          //Ambient
//          float AmbientStrength =0.1f;
//          //vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength * vec3( texture( material.Diffuse, f_Texture ) );
//           vec3 Ambient = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *AmbientStrength;
//
//      //   if(theta > Light.CutOff)
//         //{
//   
//       
////            //Diffuse
////           
//             vec3 Norm = normalize( f_Normal );
////
//          //  vec3 LightDir = normalize(Light.u_LightDirection );
//
//            float DiffuseStrength = max( dot( Norm, LightDir ),0.0 );
//             vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength);
//            //vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength * vec3(texture(material.Diffuse, f_Texture )));
//
//            //Specular 
//            vec3 ViewDir = normalize(u_CameraPos - (f_FragPos ));
//            vec3 ReflectDir = reflect( -LightDir, Norm );
//            float SpecularStrength = pow( max( dot( ViewDir, ReflectDir ), 0.0 ), material.Shininess );
////          //  vec3 Specular = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *( SpecularStrength * vec3( texture( material.Specular, f_Texture ) ) );
//           vec3 Specular = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) *( SpecularStrength  );
//
//      
//        //    
//        
//          vec3 result = ( Ambient*attenuation + Diffuse*attenuation *intensity + Specular*attenuation *intensity );
//        //  vec3 result = ( Ambient*attenuation + Diffuse*attenuation *intensity + Specular*attenuation *intensity );
//            //vec3 result = ( Ambient +Diffuse );
//
//         //   color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) ;
//           //  color =  vec4( result , 1.0) ;
//           color = texture( u_Texture, f_Texture ) * vec4( result , 1.0) * ( u_ObjectColor );
//           // color =  vec4( result , 1.0)/* * ( u_ObjectColor )*/;
////              }
////              else
////              {
////                color = texture( u_Texture, f_Texture )* vec4(Ambient, 1.0 );
////              }
        
    }
    vec3 CalulateDirectionLight(FDirectionalLight DirectionalLight, vec3 Normal, vec3 ViewDirection, FMaterial material)
    {
           
         vec3 LightDir = normalize(-DirectionalLight.Direction);
         float DiffuseStrength = max( dot( Normal, LightDir ),0.0 );
    //     vec3 Diffuse = vec3( u_LightColor.x, u_LightColor.y, u_LightColor.z ) * ( DiffuseStrength);
         vec3 Diffuse = (DirectionalLight.Diffuse) * ( DiffuseStrength) * vec3(texture(material.Diffuse, f_Texture));
   

         float AmbientStrength =0.1f;

         vec3 Ambient = DirectionalLight.Ambient * AmbientStrength;
         // Specular 
    
            vec3 ReflectDir = reflect( -LightDir, Normal );
            float SpecularStrength = pow( max( dot( ViewDirection, ReflectDir ), 0.0 ), 0.0f );

           vec3 Specular = DirectionalLight.Specular *( SpecularStrength  ) * vec3(texture(material.Specular, f_Texture));
           //vec3 Result = Ambient+ Diffuse+ Specular ;
          return (Ambient+ Diffuse+ Specular);

    }

     vec3 CalulatePointLight(FPointLight PointLight, vec3 Normal, vec3 ViewDirection, FMaterial material, vec3 FragPosition)
     {  
     
       
       vec3 LightDir = normalize(PointLight.Position - FragPosition);
         float DiffuseStrength = max( dot( Normal, LightDir ),0.0 );
       
         vec3 Diffuse = (PointLight.Diffuse) * ( DiffuseStrength) * vec3(texture(material.Diffuse, f_Texture));
//    
//
//         float AmbientStrength =0.1f;
//
         vec3 Ambient = PointLight.Ambient * vec3(texture(material.Diffuse, f_Texture));
//         // Specular 
//    
            vec3 ReflectDir = reflect( -LightDir, Normal );
            float SpecularStrength = pow( max( dot( ViewDirection, ReflectDir ), 0.0 ), 0.0f );
//
           vec3 Specular = PointLight.Specular *( SpecularStrength  ) * vec3(texture(material.Specular, f_Texture));
//
//           //Attuenation calculation
        float Distance = length(PointLight.Position - FragPosition);
       float Attenuation = 1.0/(PointLight.Constant + PointLight.Linear * Distance + PointLight.Quadratic* (Distance * Distance));
       Ambient *=Attenuation;
       Diffuse *=Attenuation;
       Specular *=Attenuation;
           
        return (Diffuse+Ambient+Specular);
//        vec3 Test;
//        return Test;
     }
##Shader End