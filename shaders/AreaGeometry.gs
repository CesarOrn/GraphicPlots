#version 330 core

uniform float antialias;
uniform float thickness;

layout (lines) in;
layout (triangle_strip, max_vertices = 6) out;

out vec2 uv;

void main(){
	
	vec4 p1Proj = gl_in[0].gl_Position;
	p1Proj.y = 0.0;

	vec4 p2Proj = gl_in[1].gl_Position;
	p2Proj.y = 0.0;

	gl_Position  =  gl_in[0].gl_Position;
	uv = vec2(0,1);
	EmitVertex();
	gl_Position  =  gl_in[1].gl_Position;
	uv = vec2(0,1);
	EmitVertex();
	gl_Position  =  p1Proj;
	uv = vec2(0,-1);
	EmitVertex();
	EndPrimitive();

	gl_Position  =  p1Proj;
	uv = vec2(0,1);
	EmitVertex();
	gl_Position  =  gl_in[1].gl_Position;
	uv = vec2(0,-1);
	EmitVertex();
	gl_Position  =  p2Proj;
	uv = vec2(0,-1);
	EmitVertex();
	EndPrimitive();
}