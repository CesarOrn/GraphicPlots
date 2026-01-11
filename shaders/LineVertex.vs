#version 330 core
uniform vec2 resolution;
uniform float antialias;
uniform float thickness;
uniform mat4 mvp;

layout (location = 0) in vec3 p;

//out float v_alpha, v_thickness;
//out vec2 v_p0, v_p1, v_p;

void main() {
    //vec4 pTrans = mvp * vec4(p,1.0);
    gl_Position = vec4(p, 1.0);
}