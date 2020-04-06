#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 u_Matrix;
void main(void)
{
    gl_Position = u_Matrix * vec4(aPos, 1.0);
}
