#version 450 core
    layout( location = 0 ) out vec4 color;
    layout( location = 1 ) out int id;
    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;
    in flat float f_ID;

    struct FMaterial
    {
        sampler2D BaseTexture;
        vec4 ObjectColor;
    };
    uniform FMaterial Material;
    float near = 0.1; 
    float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}
    void main()
    {     
//    if(f_ID  == 100)
//    {
//    color = vec4(0,0,1,1.0 );
//    }
//    else
//    {
//       color = vec4(1,0,0.0,1.0 );
//    }

         color =texture( Material.BaseTexture, f_Texture ) * vec4(  Material.ObjectColor );
      // color = vec4(f_ID/2 + 0.1,0,0.0,1.0 );

       id =  int(f_ID);
               
    }

##Shader End