#version 120  // YJC: Comment/un-comment this line to resolve compilation errors
                 //      due to different settings of the default GLSL version

//in  vec3 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


vec4 fogColor = vec4(0.7, 0.7, 0.7, 0.5);
float FogDensity = 0.09;
float fogFactor, dist;
varying vec3 FragPos;
varying vec3 Normal;
varying vec2 texCoord;

uniform vec3 globalAmbientLight;
uniform vec3 viewPos;
uniform bool pLight;
uniform bool ground;
uniform sampler2D texture;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform int fogOption;

uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * pow(intensity,15);
    diffuse *= attenuation * pow(intensity,15);
    specular *= attenuation * pow(intensity,15);
    return (ambient + diffuse + specular);
}

vec4 FragColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    if(pLight == true)
    {
        result += CalcPointLight(pointLight, norm, FragPos, viewDir);
    }
    else
    {
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    }
    // phase 3: spot light
    result = result + globalAmbientLight * material.ambient;
    FragColor = vec4(result, 1.0);
    if(ground)
        FragColor = FragColor * texture2D( texture, texCoord );

    dist = length(FragPos);
    if(fogOption == 1)//linear fog
    {
       fogFactor = (0 - dist)/(0 - 18);
       fogFactor = clamp( fogFactor, 0.0, 1.0 );

       FragColor = mix(fogColor, FragColor, 1.0 - fogFactor);
    }
    else if(fogOption == 2)// exponential fog
    {
        fogFactor = 1.0 /exp(dist * FogDensity);
        fogFactor = clamp( fogFactor, 0.0, 1.0 );

        FragColor = mix(fogColor, FragColor, fogFactor);
    }
    else if(fogOption == 3)
    {
       fogFactor = 1.0 /exp( (dist * FogDensity)* (dist * FogDensity));
       fogFactor = clamp( fogFactor, 0.0, 1.0 );

       FragColor = mix(fogColor, FragColor, fogFactor);
    }
    gl_FragColor = FragColor;
}
