#version 330 core
    layout( location = 0 ) out vec4 color;
    in vec4 f_Color;
    uniform vec4 u_Color;
    void main()
    {
        color = f_Color;
    }