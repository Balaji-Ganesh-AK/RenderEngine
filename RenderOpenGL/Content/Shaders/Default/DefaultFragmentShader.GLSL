#version 330 core
    layout( location = 0 ) out vec4 color;
    in vec4 f_Color;
    in vec2 f_Texture;
    struct Material
    {     
        sampler2D Diffuse;
    };
    uniform vec4 u_Color;
    uniform vec4 u_ObjectColor;
    uniform Material material;

    void main()
    {
        color =texture( material.Diffuse, f_Texture );
         //*vec4( u_ObjectColor)
    }