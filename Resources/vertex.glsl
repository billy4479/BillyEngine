#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec4 aTexCoord;

out vec4 color;

uniform float xOffset;

void main() {
    // color = aPos;
    color = aColor;
    gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);
}