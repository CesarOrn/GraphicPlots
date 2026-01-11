#version 330 core

uniform float antialias;
uniform float thickness;
uniform vec3 color;

out vec4 FragColor;

in vec2 uv;

void main() {

	gl_FragColor = vec4(color, 1.0);

}