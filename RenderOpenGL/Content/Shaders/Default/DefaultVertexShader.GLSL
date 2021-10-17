#version 330 core
    layout( location = 0 ) in vec4 v_Pos;
    layout( location = 1 ) in vec4 v_Color;

    out vec4 f_Color;

    void main()
    {
        //f_Color = v_Color;
    f_Color = vec4(0.5f,0.5f,0.5f,1.0f);
        gl_Position = v_Pos;
    }