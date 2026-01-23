#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    

	//float alpha = steptexture(text, TexCoords).r > 0.5;

    //vec4 sampled = vec4(1.0, 1.0, 1.0, alpha);
    //color = vec4(textColor, 1.0) * sampled;
	float d = texture(text, TexCoords).r;
	if(d >0.5){
		gl_FragColor = vec4(textColor, 1.0);
	}else if(d > 0.3){
		d = (d - 0.3)/(0.5-0.3);
		smoothstep(0.0,1.0,d);
		gl_FragColor = vec4(textColor, d*d);
	}else{
		gl_FragColor = vec4(textColor, 0.0);
	}
}