#version 150

uniform sampler2D Texture;

in vec2 FragTexCoord;
in vec4 normal;

out vec4 FragmentColor;

in vec4 FragPos;
in vec4 ViewPos;

float ambientStrength = 0.01f;
vec4 ambientLightColour = vec4(0.02f, 0.01f, 0.01, 0.1);
vec4 ambient = ambientStrength * ambientLightColour;

vec4 diffuseLightPosition1 = vec4(0.2f, 0.1f, 0.1f, 0.0f);
vec4 diffuseLightColor1 = vec4(0.2,0.1,0.1,0.1);
vec4 diffuseLightDirection1 = normalize(diffuseLightPosition1 - FragPos);
vec4 diffuse1 = max(dot(normal, diffuseLightDirection1), 0.0) * diffuseLightColor1;

vec4 diffuseLightPosition2 = vec4(0.2f, 0.1f, 0.1f, 0.0f);
vec4 diffuseLightColor2 = vec4(0.2,0.1,0.1,0.1);
vec4 diffuseLightDirection2 = normalize(diffuseLightPosition2 - FragPos);
vec4 diffuse2 = max(dot(normal, diffuseLightDirection2), 0.0) * diffuseLightColor2;

vec4 specularLightPosition = vec4(0.2f, 0.1f, 0.1f, 0.0f);
vec4 specularLightDirection = vec4(specularLightPosition - FragPos);
vec4 specularLightColor = vec4(0.1, 0.1, 0.1, 0.1);

float specularStrength = 0.01f;
vec4 viewDirection = vec4(ViewPos - FragPos);
vec4 reflectDirection = reflect(-specularLightDirection, normal);

float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);
vec4 specular = specularStrength * spec * specularLightColor;

void main() {
    FragmentColor = texture(Texture, vec2(FragTexCoord.x,-FragTexCoord.y)) * (diffuse1 + diffuse2) + (specular + ambient);
}
