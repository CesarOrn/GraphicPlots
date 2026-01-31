#version 330 core
#define PI 3.14159265359
uniform sampler2D  chebyShevPoly;

uniform float antialias;
uniform float thickness;
uniform vec4 color;

in vec2 uv;

out vec4 FragColor;

vec3 colorCode(vec3 a, vec3 b, vec3 c, vec3 d, float t){
    float tClmp = clamp(0.0,1.0,t);
    vec3 color = a + b*cos(2*PI*(c*t + d));
    return color;
}

void main() {
    
    vec3 a = vec3(0.46,0.46,0.46);
    vec3 b = vec3(0.46,0.46,0.46);
    vec3 c = vec3(0.7,0.0,0.5);
    vec3 d = vec3(0.52,0.52,0.52);
    vec2 uvShift = (uv * 2.0) -1.0;
    float dens = texture(chebyShevPoly,uv).r;
    vec3 color = colorCode(a,b,c,d,dens/0.12);
	gl_FragColor = vec4(color, 1.0);
}