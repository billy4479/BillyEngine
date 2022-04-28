#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 color;
out vec2 TexCoord;

uniform mat4 Transform;

void main() {
    // color = aPos;
    color = aColor;
    TexCoord = aTexCoord;

    gl_Position = Transform * vec4(aPos, 1);
}