#version 150

//Globals
uniform mat4 mvp;
uniform mat4 mv;
uniform mat4 m;

//Inputs
in vec3 in_pos;
in vec3 in_uv;
in vec3 in_normal;

//Outputs
out vec3 ex_uv;
out vec3 ex_normal;
out vec3 frag_pos;

void main(void) {
	gl_Position = mvp * vec4(in_pos, 1.0);
	frag_pos = vec3(m *vec4(in_pos, 1.0));
	ex_uv = in_uv;
	ex_normal = in_normal;
}
