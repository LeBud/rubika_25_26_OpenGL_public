#version 330 core
    out vec4 FragColor;
    
    in vec3 ourColor;
    in vec2 TexCoord;
    
    // texture samplers
    uniform sampler2D texture1;
    uniform sampler2D texture2;
    
    in vec2 uv;
    uniform float uTime;
    
    void main()
    {
        float wave = sin(uv.x * 10.0 + uTime) * 0.5 + 0.5;
        float wave2 = cos(uv.y * 10.0 + uTime * 1.2) * 0.5 + 0.5;
    
        vec3 color = vec3(sin(uv.x * 8.0 + uTime),
                          sin(uv.y * 6.0 + uTime * 1.3),
                          sin(uv.x * 5.0 + uv.y * 5.0 + uTime * 1.7)) * 0.5 + 0.5;
    
        FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord) * vec4(color, 1), 0.4);
    }