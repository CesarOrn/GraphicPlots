#version 330 core

uniform sampler2D chebyShevPoly;

uniform float antialias;
uniform float thickness;
uniform vec4 color;

in vec2 uv;

out vec4 FragColor;

void main() {
	float res = 0.0f;
    ivec2 index;
    for(int i = 0; i < 128; i++){
        for(int j = 0; j < 128; j++){
            index = ivec2(i,j);
            res = res + texelFetch(chebyShevPoly, index,0).r * cos(i*acos(uv.x*2.0 -1.0))*cos(j*acos(uv.y*2.0 -1.0));
        }
    }
    //res = clamp(res,0.0,1.0);
	gl_FragColor = vec4(res ,0.0,0.0, 1.0);
}