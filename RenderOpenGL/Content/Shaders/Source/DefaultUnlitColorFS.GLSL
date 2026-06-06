#version 330 core
    layout( location = 0 ) out vec4 color;
    layout( location = 1 ) out int id;
    in vec4 f_Color;
    flat in int f_ID;
    void main()
    {
       color = f_Color;
       id = f_ID;
    }

##Shader End