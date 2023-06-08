#version 120
attribute highp vec4 posAttr;
attribute vec2 texCord;

uniform highp mat4 rotateMatrix;
uniform highp mat4 translation;
//camera
uniform highp mat4 view;
varying vec4 resPos;
varying vec2 uvMap;
varying vec3 localNorm;

void main() {
    resPos = translation * rotateMatrix * posAttr;
    gl_Position = view * resPos;

    uvMap = texCord;
    localNorm = vec4(translation * rotateMatrix * normalize(posAttr)).xyz;
}
