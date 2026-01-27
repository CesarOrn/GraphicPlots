#version 330 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec2 UV;

uniform mat4 mvp;
out vec2 uv;
void main(){
    uv = UV;
    gl_Position =mvp*vec4(p.xy, 0.0, 1.0);
}