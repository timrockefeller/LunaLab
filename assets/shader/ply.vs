#version 330 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoords;// discord


out vec4 FragPos;
out vec3 Normal;
out vec4 Color;
out vec2 TexCoords;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = aPos;
    Normal = aNormal;
    TexCoords = aTexCoords;    
    Color = aColor;
    gl_Position = projection * view * model * vec4(aPos);
    gl_PointSize = 10.0f;
}