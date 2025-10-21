#version 330 core
    out vec4 FragColor;
    
    in vec2 TexCoord;
    
    uniform sampler2D texture1;
    uniform sampler2D texture2;
    uniform vec3 color;
    
    uniform float uTime;
    
    void main()
    {
        //FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord) * vec4(color, 1), 0.4);
        FragColor = vec4(color, 1);
    }