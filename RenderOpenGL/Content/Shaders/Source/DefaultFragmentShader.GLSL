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
 
    void main()
    {     
        color =texture( Material.BaseTexture, f_Texture ) * vec4(  Material.ObjectColor );
               
    }

##Shader End