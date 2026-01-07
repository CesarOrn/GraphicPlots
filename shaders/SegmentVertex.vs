#version 330 core
//uniform vec2 resolution;
uniform float antialias;
uniform float thickness;
uniform float len;
uniform mat2 model;
uniform vec2 point;

layout (location = 0) in vec2 uv;

out float v_alpha, v_thickness;
out vec2 v_p0, v_p1, v_p;

void main() {
    v_thickness = thickness;
    v_alpha = 1.0;
   
    float t = v_thickness/2.0  + antialias;
    float l = len;
    vec2 uvCenter = 2.0f*uv-1.0;

    vec2 T = model * vec2(1.0,0.0);
    vec2 O = vec2(-T.y , T.x);
    
    vec2 p = point + uv.x*T*l + uvCenter.x*T*t + uvCenter.y*O*t;
    vec2 aspect = vec2(1,resolution.y/resolution.x);
    gl_Position = vec4(p, 0.0, 1.0);

    T = vec2(1.0, 0.0);
    O = vec2(0.0, 1.0);
    p = uv.x*T*l + uvCenter.x*T*t + uvCenter.y*O*t;

    v_p0 = vec2(0.0, 0.0);
    v_p1 = vec2(  l, 0.0);
    v_p  = p;

}