#pragma once
#include "HumbugEngine/Camera.h"
#include "HumbugEngine/Vector.h"

#include <GL/glew.h>
#include <vector>
#include <map>
#include <memory>

#include "HumbugEngine/Material.h"
#include "HumbugEngine/Texture.h"

class UIQuad
{
public:
	static const int NUM_VBOS = 4;

	UIQuad(const char* fname);
	~UIQuad();

	void Draw();

	void DebugDraw(const Camera& cam, const Matrix4& objMat);

private:
	// void AddFace(
	// const std::vector<float>& vert_palette, const std::vector<float>& uv_palette,
	// uint32_t a, uint32_t at, uint32_t b, uint32_t bt, uint32_t c, uint32_t ct, bool is3DTex);

	GLuint vao;
	GLuint vbo[NUM_VBOS];

	Vector3 position;
	Vector3 scale;

	std::vector<float> verts;
	std::vector<float> uvs;
	std::vector<float> normals;

	std::shared_ptr<Texture> texture;
};