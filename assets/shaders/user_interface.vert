#version 150

//Globals
uniform mat4 u_Projection;
uniform mat4 u_Scale;

//Inputs
in vec3 in_pos;
in vec2 in_uv;

//Outputs
out vec2 ex_uv;

void main(void) {
	gl_Position = u_Projection * u_Scale * vec4(in_pos, 1.0);
	ex_uv = in_uv;
} 