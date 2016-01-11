#version 330 core
layout (location = 0) in vec3 position;
layout (location = 7) in mat4 instanceMatrixRain;


uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * instanceMatrixRain * vec4(position, 1.0f);
}
