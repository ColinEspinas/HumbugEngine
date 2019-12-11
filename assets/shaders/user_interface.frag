#version 150
precision highp float;

//Inputs
uniform sampler2D tex;
in vec2 ex_uv;

//Outputs
out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = vec4(texture(tex, ex_uv).rgb, 1.0);
} 