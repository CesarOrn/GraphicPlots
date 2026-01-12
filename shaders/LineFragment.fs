#version 330 core

uniform float antialias;
uniform float thickness;
uniform vec4 color;

out vec4 FragColor;

in vec2 uv;

void main() {
	float width = thickness/2.0;

	float d = abs(uv.y) - width;
	if(d < 0){
		gl_FragColor = vec4(color.rgb, 1.0);
	}else if(d < antialias){
		d = 1-d/antialias;
		gl_FragColor = vec4(color.rgb, d*d);
	}else{
		gl_FragColor = vec4(color.rgb, 0.0);
	}
}