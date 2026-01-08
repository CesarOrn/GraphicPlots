#version 330 core
uniform vec2 resolution;
uniform float antialias;
uniform float thickness;
uniform mat2 model;

layout (location = 0) in vec3 p;

//out float v_alpha, v_thickness;
//out vec2 v_p0, v_p1, v_p;

void main() {
    vec2 pTrans = model * p.xy;
    gl_Position = vec4(pTrans, 0.0, 1.0);
}