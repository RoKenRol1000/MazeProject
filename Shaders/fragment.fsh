#version 120
uniform sampler2D texture;
uniform sampler2D textureNormalMap;
uniform float specularReflection;
varying vec2 uvMap;
varying vec3 localNorm;
varying vec4 resPos;
varying vec3 camPos;

//point light
uniform vec3 pointLightPos;
uniform vec4 pointLightDiffColor;
uniform vec4 pointLightSpecColor;

uniform vec3 pointLightAtt;
//backgroud light
uniform vec4 globalAmbient;
uniform float ambientIntesity;

vec3 calcNormalFromNormalmap(vec3 localNormal, vec2 uv)
{
    // Рассчитываем базисные вектора с.о. нормали (tangent space)
    vec3 n = normalize( localNormal.xyz );
    vec3 t = normalize( cross(n, vec3(1,1,1)) );
    vec3 b = cross(n, t);
    // Достаём нормаль из карты высот
    vec3 normal = texture2D( textureNormalMap, uv ).rgb;
    normal = normalize( normal * 2.0 - 1.0 );
    // Рассчитываем результирующую нормаль
    vec3 resultingNormal = normalize( normal.x * t + normal.y * b + normal.z * localNorm );

    return resultingNormal;

}


void main() {
    vec3 resNorm = calcNormalFromNormalmap(localNorm, uvMap);
    vec3 viewDir = normalize(resPos.xyz - camPos);

    float attenuation = 3.0/(pointLightAtt.x + pointLightAtt.y * distance(pointLightPos, resPos.xyz) + pointLightAtt.z * pow(distance(pointLightPos, resPos.xyz), 2.0));
    vec3 pointLightDir = normalize(pointLightPos - resPos.xyz);

    vec3 H = normalize(-viewDir + pointLightDir);
    vec4 pointDiffColor = pointLightDiffColor * max(dot(pointLightDir, resNorm), 0.0);
    vec4 pointSpecColor = pointLightSpecColor * pow(max(dot(resNorm, H) , 0.0), specularReflection);

    vec3 ambientLight = globalAmbient.xyz * ambientIntesity;
    vec3 diffuseLight = pointDiffColor.xyz * attenuation;
    vec3 specularLight = pointSpecColor.xyz * attenuation;
    gl_FragColor = texture2D(texture, uvMap) * vec4(ambientLight + diffuseLight + specularLight, 1.0);
}
