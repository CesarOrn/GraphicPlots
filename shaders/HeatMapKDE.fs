#version 330 core

uniform samplerBuffer chebyShevPoly;

uniform float antialias;
uniform float thickness;
uniform vec4 color;

in vec2 uv;

out vec4 FragColor;

void main() {
	float res = 0.0;
    ivec2 index;
    float theta_x = acos(uv.x * 2.0 -1.0);
    float theat_y = acos(uv.y * 2.0 -1.0);
    for(int j = 0; j < 20;j++){
        for(int i = 0; i < 20;i++){
            index = ivec2(i,j);
            float a = texelFetch(chebyShevPoly, i + 128 * j).r;
            float i_f = i;
            float j_f = j;

            res = res + a * cos(i_f*theta_x)*cos(j_f*theat_y);
        }
    }
    //res = clamp(res,0.0,1.0);
    vec3 color = mix(vec3(0.1,0.2,0.0),vec3(0.75,0.4,0.0),res/0.08);
	gl_FragColor = vec4(color, 1.0);
}