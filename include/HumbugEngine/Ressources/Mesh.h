#pragma once
#include "HumbugEngine/Ressources/Ressource.h"
#include "HumbugEngine/Ressources/Material.h"
#include "HumbugEngine/Components/Collider.h"
#include "HumbugEngine/Components/Camera.h"
#include "HumbugEngine/Ressources/Texture.h"
#include "HumbugEngine/Ressources/Shader.h"
#include <GL/glew.h>
#include <vector>
#include <map>


class Mesh : public Ressource {
public:
  static const int NUM_VBOS = 3;

  Mesh(std::string _path);
  ~Mesh();

  void Draw();

  void DebugDraw(const Camera& cam, const Matrix4& objMat);

  void Use() override;

  std::vector<Collider> colliders;

  std::shared_ptr<Texture> texture;
  std::shared_ptr<Shader> shader;

private:
  void _Load(std::string _path) override;

  void AddFace(
    const std::vector<float>& vert_palette, const std::vector<float>& uv_palette,
    uint32_t a, uint32_t at, uint32_t b, uint32_t bt, uint32_t c, uint32_t ct, bool is3DTex);

  GLuint vao;
  GLuint vbo[NUM_VBOS];

  std::vector<float> verts;
  std::vector<float> uvs;
  std::vector<float> normals;

  bool m_is3DTex = false;

  bool isUsingMaterials = false;    // TO CHANGE
  std::vector<Material> materials;  // TO REMOVE
};

typedef std::vector<std::shared_ptr<Mesh>> PMeshVec;
