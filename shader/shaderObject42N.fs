
#version 330 core
out vec4 FragColor;

struct lightning {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};

struct textu {
    sampler2D diffuse; 
    sampler2D specular; 
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;
flat in int Index;

uniform textu t[4];
uniform bool nbTex;
uniform vec3 viewPos;
uniform lightning material[32];
uniform lightning lightObj;
uniform Light light;

void main()
{
    // vec3 texColor = texture(t[0].diffuse, TexCoords).rgb;
    
    vec3 ambient = light.ambient * material[Index].ambient ;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);

    vec3 diffuse = light.diffuse * (diff * material[Index].diffuse) *attenuation;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material[Index].shininess);
    vec3 specular = light.specular * (spec * material[Index].specular) * attenuation;

    vec3 result = ambient + diffuse + specular;
    
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(normalize(Normal) * 0.5 + 0.5, 1.0);
}