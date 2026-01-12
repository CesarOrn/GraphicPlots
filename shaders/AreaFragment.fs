#version 330 core

uniform float antialias;
uniform float thickness;
uniform vec4 color;

out vec4 FragColor;

in vec2 uv;

void main() {

	gl_FragColor = color;

}