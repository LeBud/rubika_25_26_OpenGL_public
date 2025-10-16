#version 330 core
    in vec3 aPos;
    out vec2 uv;
    
    void main()
    {
       gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
       uv = aPos.xy * 0.5 + 0.5;
    }