#version 330 core

layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec2 texCord;
layout(location = 2) in vec3 norm;

uniform mat4 rotateMatrix;
uniform mat4 translation;
uniform mat4 projection;
uniform mat4 view;

out vec4 resPos;
out vec2 uvMap;
out vec3 localNorm;

void main() {
    resPos = translation * rotateMatrix * posAttr;
    gl_Position = projection * view * resPos;

    uvMap = texCord;
    localNorm = mat3(translation * rotateMatrix) * norm;
}
