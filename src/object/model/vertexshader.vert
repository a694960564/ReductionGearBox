#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 u_Matrix;
uniform mat4 u_model;
uniform mat3 u_normalMatrix;
out vec3 Normal;
out vec3 FragPos;
void main(void)
{
    gl_Position = u_Matrix * vec4(aPos, 1.0);
    FragPos = vec3(u_model * vec4(aPos, 1.0));
//    Normal = u_normalMatrix * aNormal;
    Normal = vec3(u_model * vec4(aNormal, 1.0));
}
