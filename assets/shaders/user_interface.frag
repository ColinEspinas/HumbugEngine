#version 150
precision highp float;

//Inputs
uniform sampler2D tex;
in vec2 ex_uv;

//Outputs
out vec4 gl_FragColor;

void main(void) {
	if (texture(tex, ex_uv).rgb == vec3(1.0,0.0,1.0)) {
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	} else {
		gl_FragColor = vec4(texture(tex, ex_uv).rgb, 1.0);
	}
} 