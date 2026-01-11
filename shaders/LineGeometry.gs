#version 330 core

uniform float antialias;
uniform float thickness;
uniform mat4 mvp;

layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 6) out;

out vec2 uv;

void main(){
	float width = thickness/2.0 + antialias;

	vec4 t0 = normalize(gl_in[1].gl_Position - gl_in[0].gl_Position);
	vec4 t1 = normalize(gl_in[2].gl_Position - gl_in[1].gl_Position);
	vec4 t2 = normalize(gl_in[3].gl_Position - gl_in[2].gl_Position);

	vec2 n0 = vec2(-t0.y, t0.x);
	vec2 n1 = vec2(-t1.y, t1.x);
	vec2 n2 = vec2(-t2.y, t2.x);

	vec2 m0 = normalize(n0 + n1);
	vec2 m1 = normalize(n1 + n2);

	float dy0 = width/ dot(m0,n1);
	float dy1 = width/ dot(m1,n2);

	gl_Position  =  mvp * vec4(gl_in[1].gl_Position.xy + m0 * dy0, 0.0, 1.0);
	uv = vec2(0,width);
	EmitVertex();
	gl_Position  =  mvp * vec4(gl_in[2].gl_Position.xy + m1 * dy1, 0.0, 1.0);
	uv = vec2(0,width);
	EmitVertex();
	gl_Position  =  mvp * vec4(gl_in[1].gl_Position.xy - m0 * dy0, 0.0, 1.0);
	uv = vec2(0,-width);
	EmitVertex();
	EndPrimitive();

	gl_Position  =  mvp * vec4(gl_in[2].gl_Position.xy + m1 * dy1, 0.0, 1.0);
	uv = vec2(0,width);
	EmitVertex();
	gl_Position  =  mvp * vec4(gl_in[2].gl_Position.xy - m1 * dy1, 0.0, 1.0);
	uv = vec2(0,-width);
	EmitVertex();
	gl_Position  =  mvp * vec4(gl_in[1].gl_Position.xy - m0 * dy0, 0.0, 1.0);
	uv = vec2(0,-width);
	EmitVertex();
	EndPrimitive();
}