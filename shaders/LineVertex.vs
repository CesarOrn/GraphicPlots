#version 330 core
//uniform vec2 resolution;
uniform float antialias;
uniform float thickness;
uniform float len;
uniform mat2 model;

layout (location = 0) in vec3 pointPrev;

out float v_alpha, v_thickness;
out vec2 v_p0, v_p1, v_p;

void main() {

    gl_Position = vec4(p, 0.0, 1.0);


}