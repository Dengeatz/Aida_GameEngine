#version 330 core
in vec2 texCoord;
in vec3 color;
out vec4 FragColor;

uniform sampler2D tex;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(tex, texCoord), texture(texture2, texCoord), 0.5);
}