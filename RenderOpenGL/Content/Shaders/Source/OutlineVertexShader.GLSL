#version 450 core
    layout( location = 0 ) in vec3 v_Pos;
    layout( location = 2 ) in vec3 v_Normal;

    uniform mat4 u_MVP;             // projection * view * model
    uniform vec3 u_ViewportSize;    // (width, height, unused) in pixels
    uniform float u_OutlinePixels;  // outline thickness in pixels

    void main()
    {
        vec4 clipPos    = u_MVP * vec4( v_Pos, 1.0 );
        vec4 clipNormal = u_MVP * vec4( v_Normal, 0.0 );

        vec2 viewport = u_ViewportSize.xy;

        // Surface-normal direction in pixel space.
        vec2 pixelDir = clipNormal.xy * viewport;
        float len = length( pixelDir );
        pixelDir = ( len > 1e-5 ) ? pixelDir / len : vec2( 0.0 );

        // Push the vertex outward by a constant number of PIXELS. Converting that pixel offset
        // back to NDC and multiplying by w keeps the thickness constant after the perspective
        // divide, so the outline is the same screen size for every object (any size, any distance).
        vec2 ndcOffset = ( pixelDir / viewport ) * 2.0 * u_OutlinePixels;
        clipPos.xy += ndcOffset * clipPos.w;

        gl_Position = clipPos;
    }


##Shader End