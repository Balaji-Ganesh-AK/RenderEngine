#version 330 core
    layout( location = 0 ) out vec4 color;
    in vec4 f_Color;
    in vec2 f_Texture;

    uniform vec4 u_Color;
    uniform vec4 u_ObjectColor;
    uniform sampler2D u_Texture;
    void main()
    {
        color = /*texture(u_Texture, f_Texture)*/ vec4( u_ObjectColor * u_Color);
    }