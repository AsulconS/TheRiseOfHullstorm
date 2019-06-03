#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;

out vec2 UV;

uniform float depth;
uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos + offset, depth, 1.0f);
    UV = aUV;
}
