#version 330 core

in vec3 normal_location;
in vec3 frag_loc;
in vec2 text_cd;
out vec4 FragColor;

struct Luz {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Luz light;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    float light_cte = 1.0f;
    float light_linear = 0.09f;
    float light_quadratic = 0.032f;

    vec3 cam_dir = vec3(0.0, 0.0,-1.0f);
    float cutOff = cos(radians(10.0f));
    

    float distance    = length(light.position - frag_loc);
    float attenuation = 1.0 / (light_cte + light_linear * distance + 
    		    light_quadratic * (distance * distance)); 

    // ambient
    

    // diffuse
   // vec3 norm = normalize(normal_location);
     vec3 norm = texture(ourTexture,text_cd).rgb;
     norm = normalize( norm* 2.0 - 1.0);
    vec3 lightDir = normalize(light.position - frag_loc);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff* texture(ourTexture1, text_cd).rgb);


  
    // specular
    vec3 viewVector = normalize(vec3(0.0,0.0,0.0) - frag_loc);
    vec3 reflectVetor = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewVector, reflectVetor), 0.0), material.shininess);
    vec3 specular = light.specular * (spec*texture(ourTexture2,text_cd).rgb);

    float theta = dot(cam_dir,normalize(-viewVector));

    vec3 ambient = vec3(0.0,0.0,0.0);



    if(theta > cutOff){
         ambient = light.ambient * texture(ourTexture1, text_cd).rgb;
    }

    ambient  *= attenuation; 
    diffuse  *= attenuation;
    specular *= attenuation; 

    vec3 result = specular + ambient + diffuse;
    FragColor = vec4(result, 1.0);     
    

}