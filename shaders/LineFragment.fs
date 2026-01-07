#version 330 core
uniform float antialias;

in float v_thickness;
in vec2 v_p0, v_p1, v_p;

out vec4 FragColor;

void main() {
	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}