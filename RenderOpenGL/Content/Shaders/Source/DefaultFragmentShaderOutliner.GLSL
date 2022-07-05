#version 330 core
    layout( location = 0 ) out vec4 color;
    in vec3 f_Normal;
    in vec2 f_Texture;
    in vec3 f_FragPos;

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
       //color =texture( Material.BaseTexture, f_Texture ) * vec4(  Material.ObjectColor );
       color  = vec4(1.0, 1.0, 0.0, 1.0);
//     float depth = LinearizeDepth(gl_FragCoord.z) / far; 
//     color = vec4(vec3(depth), 1.0);
               
    }

##Shader End