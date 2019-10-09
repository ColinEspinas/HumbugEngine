#version 150
precision highp float;

// Globals
uniform vec3 viewPos;

// Material
struct Material {
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

// Light
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

#define MAX_LIGHTS 64

uniform int dirLightsCount;
uniform int pointLightsCount;
uniform DirLight dirLights[MAX_LIGHTS];
uniform PointLight pointLights[MAX_LIGHTS];

// Inputs
in vec2 ex_uv;
in vec3 ex_normal;
in vec3 frag_pos;

// Outputs
out vec4 gl_FragColor;

// Function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(void) {

	vec3 norm = normalize(ex_normal);
	vec3 viewDir = normalize(viewPos - frag_pos);

	vec3 result;

	for(int i = 0; i < dirLightsCount; ++i)
		result += CalcDirLight(dirLights[i], norm, viewDir); 
	
	for(int i = 0; i < pointLightsCount; ++i)
		result += CalcPointLight(pointLights[i], norm, frag_pos, viewDir); 

	gl_FragColor = vec4(result, 1.0);

//	 Base shader
//	float s = dot(ex_normal, LIGHT)*0.5 + 0.5;
//	gl_FragColor = vec4(texture(tex, ex_uv).rgb * s, 1.0);
}

// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {

	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, ex_uv));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ex_uv));
	vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 viewDir) {

    vec3 lightDir = normalize(light.position - frag_pos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float diff = max(dot(normal, lightDir), 0.0);
    
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, ex_uv));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, ex_uv));
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
