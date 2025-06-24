#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 texture_coord;
out vec2 texCoord;
out vec3 color;

uniform mat4 transform;

void main()
{ 
    gl_Position = transform * vec4(aPos, 1.0);
    texCoord = texture_coord;
    color = vec3(1.0f, 0.5f, 1.0f);
}