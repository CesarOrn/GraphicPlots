#version 330 core

layout (line_strip) in;
layout (triangle_strip, max_vertices = 6)

void main(){
	vec4 t0 = gl_in[0].gl_Position - gl_in[1].gl_Position;
	vec4 t1 = gl_in[1].gl_Position - gl_in[2].gl_Position;
	vec4 t2 = gl_in[2].gl_Position - gl_in[3].gl_Position;

	vec2 n0 = vec2(-t0.y, t0.x);
	vec2 n1 = vec2(-t1.y, t1.x);
	vec2 n2 = vec2(-t2.y, t2.x);

	vec2 m0 = normalize(n0 + n1);
	vec2 m1 = normalize(n1 + n2);

	glPosition =  vec4(gl_in[1].gl_Positionxy + m0 * 0.1, 0.0, 1.0);
	EmitVertex();
	glPosition =  vec4(gl_in[2].gl_Positionxy + m1 * 0.1, 0.0, 1.0);
	EmitVertex();
	glPosition =  vec4(gl_in[1].gl_Positionxy - m0 * 0.1, 0.0, 1.0);
	EmitVertex();
	EndPrimative();

	glPosition =  vec4(gl_in[2].gl_Positionxy + m1 * 0.1, 0.0, 1.0);
	EmitVertex();
	glPosition =  vec4(gl_in[2].gl_Positionxy - m1 * 0.1, 0.0, 1.0);
	EmitVertex();
	glPosition =  vec4(gl_in[1].gl_Positionxy - m0 * 0.1, 0.0, 1.0);
	EmitVertex();
	EndPrimative();
}