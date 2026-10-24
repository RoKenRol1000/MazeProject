#version 330 core

// Vars from vertex.vsh
in vec4 resPos;
in vec2 uvMap;
in vec3 localNorm;

// textures + materials
uniform sampler2D texture;
uniform sampler2D textureNormalMap;
uniform float specularReflection;
uniform vec3 camPos;

// point light
uniform vec3 pointLightPos;
uniform vec4 pointLightDiffColor;
uniform vec4 pointLightSpecColor;
uniform vec3 pointLightAtt;

// ambient light
uniform vec4 globalAmbient;
uniform float ambientIntesity;

// pixel color
out vec4 fragColor;

vec3 calcNormalFromNormalmap(vec3 localNormal, vec2 uv)
{
    vec3 n = normalize(localNormal.xyz);
    vec3 t = normalize(cross(n, vec3(1.0, 1.0, 1.0)));
    vec3 b = cross(n, t);

    // high map
    vec3 normal = texture(textureNormalMap, uv).rgb;
    normal = normalize(normal * 2.0 - 1.0);

    vec3 resultingNormal = normalize(normal.x * t + normal.y * b + normal.z * localNormal);

    return resultingNormal;
}

void main() {
    vec3 resNorm = calcNormalFromNormalmap(localNorm, uvMap);
    vec3 viewDir = normalize(resPos.xyz - camPos);

    float dist = distance(pointLightPos, resPos.xyz);
    float attenuation = 3.0 / (pointLightAtt.x + pointLightAtt.y * dist + pointLightAtt.z * pow(dist, 2.0));
    vec3 pointLightDir = normalize(pointLightPos - resPos.xyz);

    vec3 H = normalize(-viewDir + pointLightDir);
    vec4 pointDiffColor = pointLightDiffColor * max(dot(pointLightDir, resNorm), 0.0);
    vec4 pointSpecColor = pointLightSpecColor * pow(max(dot(resNorm, H), 0.0), specularReflection);

    vec3 ambientLight = globalAmbient.xyz * ambientIntesity;
    vec3 diffuseLight = pointDiffColor.xyz * attenuation;
    vec3 specularLight = pointSpecColor.xyz * attenuation;

    fragColor = texture(texture, uvMap) * vec4(ambientLight + diffuseLight + specularLight, 1.0);
}
