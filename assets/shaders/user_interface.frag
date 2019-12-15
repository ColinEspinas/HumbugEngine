#version 150
precision highp float;

//Inputs
uniform sampler2D tex;
in vec2 ex_uv;

//Outputs
out vec4 gl_FragColor;

void main(void) {
	if (texture(tex, ex_uv).r >= 0.5
		&& texture(tex, ex_uv).g <= 0.5
		&& texture(tex, ex_uv).b >= 0.5) {
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	} else {
		gl_FragColor = vec4(texture(tex, ex_uv).rgb, 1.0);
	}
} 