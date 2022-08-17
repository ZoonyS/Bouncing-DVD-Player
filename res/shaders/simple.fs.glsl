#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);;  
    if (texColor.a < 0.1) discard;
    FragColor = texColor;
}
