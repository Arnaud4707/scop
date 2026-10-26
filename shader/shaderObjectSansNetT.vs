
#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool texWorld;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model *  vec4(aPos, 1.0));
    if (texWorld)
        TexCoords = FragPos.xz * 1.0;
    else
        TexCoords = aPos.xz * 1.0;
}
