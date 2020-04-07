#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 lightPos;
uniform vec3 viewPos;
vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 u_ObjectColor;
float ambientStrength = 0.5;
float specularStrength = 0.5;
void main(void)
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    FragColor = vec4(result, 1.0);
}
