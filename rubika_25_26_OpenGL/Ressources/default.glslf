#version 330 core
    out vec4 FragColor;
    in vec2 uv;
    
    uniform float iTime;
    
    void main()
    {
        float wave = sin(uv.x * 10.0 + iTime) * 0.5 + 0.5;
        float wave2 = cos(uv.y * 10.0 + iTime * 1.2) * 0.5 + 0.5;
        
        vec3 color = vec3(sin(uv.x * 8.0 + iTime),
                       sin(uv.y * 6.0 + iTime * 1.3),
                       sin(uv.x * 5.0 + uv.y * 5.0 + iTime * 1.7)) * 0.5 + 0.5;
        
        FragColor = vec4(color, 1.0f);
    }