#version 460 core

out vec4 FragColor;
in vec4 color;
in vec2 TexCoord;

uniform sampler2D Texture;

void main() {
    vec4 textureColor = texture(Texture, TexCoord);
    // FragColor = mix(textureColor, color, 0.25);
    FragColor = textureColor;
}