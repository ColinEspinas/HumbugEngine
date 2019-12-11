#include "HumbugEngine/UIQuad.h"
#include "HumbugEngine/Resources.h"

#include <fstream>
#include <sstream>

UIQuad::UIQuad(const char* fname) {
	//Open the file for reading

	texture = AquireTexture(fname);

	std::vector<float> color = { 1.0f,1.0f,1.0f };

	verts = {-1, 1, -1, -1, 1, 1, 1, -1};

	//Setup GL
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(NUM_VBOS, vbo);
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), verts.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}
	// {
	// 	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	// 	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), uvs.data(), GL_STATIC_DRAW);
	// 	glEnableVertexAttribArray(1);
	// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	// }
	// {
	// 	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	// 	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), normals.data(), GL_STATIC_DRAW);
	// 	glEnableVertexAttribArray(2);
	// 	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// }
	// {
	// 	// TO MODIFY -----------------------------------------
	// 	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	// 	glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(color[0]), color.data(), GL_STATIC_DRAW);
	// }
}

UIQuad::~UIQuad() {
	glDeleteBuffers(NUM_VBOS, vbo);
	glDeleteVertexArrays(1, &vao);
}

void UIQuad::Draw() {
	if (texture) {
	  texture->Use();
	}
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)verts.size());
}

void UIQuad::DebugDraw(const Camera& cam, const Matrix4& objMat) {
	
}