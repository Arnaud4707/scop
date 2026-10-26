
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
        vec3 texColor = texture(t[Index].diffuse, TexCoords).rgb;
        
        vec3 ambient = light.ambient * material[Index].ambient * texColor;
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(light.position - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);

        vec3 diffuse = light.diffuse * (diff * material[Index].diffuse * texColor);

        vec3 result = ambient + diffuse;
        
        FragColor = vec4(result, 1.0);
    }