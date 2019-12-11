#version 150

//Globals
uniform mat4 projection;

//Inputs
in vec3 in_pos;
in vec2 in_uv;

//Outputs
out vec2 ex_uv;

void main(void) {
	gl_Position = projection * vec4(in_pos, 1.0);
	ex_uv = in_uv;
} 