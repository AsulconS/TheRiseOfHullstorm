#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform sampler2D spriteTexture;

void main()
{
    FragColor = texture(spriteTexture, UV);
}
