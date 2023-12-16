#version 120
attribute highp vec4 posAttr;
attribute vec2 texCord;
attribute vec3 norm;

uniform highp mat4 rotateMatrix;
uniform highp mat4 translation;
uniform highp mat4 projection;
//camera
uniform highp mat4 view;
varying vec4 resPos;
varying vec2 uvMap;
varying vec3 localNorm;

void main() {
    resPos = translation * rotateMatrix * posAttr;
    gl_Position = projection * view * resPos;

    uvMap = texCord;
    localNorm = vec4(translation * rotateMatrix * vec4(norm, 0.0)).xyz;
}
