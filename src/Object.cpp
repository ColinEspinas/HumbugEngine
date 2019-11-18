#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Ressources/Mesh.h"
#include "HumbugEngine/Ressources/Shader.h"
#include "HumbugEngine/Ressources/Texture.h"
#include "HumbugEngine/Objects/Player.h"

Object::Object() :
  m_pos(0.0f),
  m_euler(0.0f),
  m_scale(1.0f),
  p_scale(1.0f)
{
	// if (!material) material = std::make_shared<Material>("__Default");
}

void Object::Reset() {
  m_pos.SetZero();
  m_euler.SetZero();
  m_scale.SetOnes();
  p_scale = 1.0f;
}

void Object::Draw(const Camera& cam, uint32_t curFBO) {
  for (auto C : m_components)
    if (ComponentCast::isFrom<MeshRenderer>(C))
      ComponentCast::Cast<MeshRenderer>(C)->Draw(cam, LocalToWorld(), WorldToLocal().Transposed(), cam.Matrix() * LocalToWorld());
  // if (shader && mesh) {
	// const Matrix4 m = LocalToWorld();
	// const Matrix4 mv = WorldToLocal().Transposed();
	// const Matrix4 mvp = cam.Matrix() * LocalToWorld();
	// shader->Use();
	// if (texture) {
	//   texture->Use();
	// }
	// material->Use(shader);
	// shader->SetM(m.m);
	// shader->SetCam(GH_PLAYER->CamToWorld());
	// shader->SetMVP(mvp.m, mv.m);
	// mesh->Draw();
  // }
}

Vector3 Object::Forward() const {
  return -(Matrix4::RotZ(m_euler.z) * Matrix4::RotX(m_euler.x) * Matrix4::RotY(m_euler.y)).ZAxis();
}

Matrix4 Object::LocalToWorld() const {
  return Matrix4::Trans(m_pos) * Matrix4::RotY(m_euler.y) * Matrix4::RotX(m_euler.x) * Matrix4::RotZ(m_euler.z) * Matrix4::Scale(m_scale * p_scale);
}

Matrix4 Object::WorldToLocal() const {
  return Matrix4::Scale(1.0f / (m_scale * p_scale)) * Matrix4::RotZ(-m_euler.z) * Matrix4::RotX(-m_euler.x) * Matrix4::RotY(-m_euler.y) * Matrix4::Trans(-m_pos);
}

void Object::DebugDraw(const Camera& cam) {
  if (this->Contain<MeshRenderer>())
    for (auto Mesh : ComponentCast::Cast<MeshRenderer>(GetComponent<MeshRenderer>())->GetAllMesh())
      Mesh->DebugDraw(cam, LocalToWorld());
}