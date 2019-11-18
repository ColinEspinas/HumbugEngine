#include "HumbugEngine/Object.h"
#include "HumbugEngine/Mesh.h"
#include "HumbugEngine/Shader.h"
#include "HumbugEngine/Texture.h"
#include "HumbugEngine/Player.h"

Object::Object() :
  pos(0.0f),
  euler(0.0f),
  scale(1.0f),
  p_scale(1.0f) {
	if (!material) material = std::make_shared<Material>("__Default");
}

void Object::Reset() {
  pos.SetZero();
  euler.SetZero();
  scale.SetOnes();
  p_scale = 1.0f;
}

void Object::Draw(const Camera& cam, uint32_t curFBO) {
  if (shader && mesh) {
	const Matrix4 m = LocalToWorld();
	const Matrix4 mv = WorldToLocal().Transposed();
	const Matrix4 mvp = cam.Matrix() * LocalToWorld();
	shader->Use();
	if (texture) {
	  texture->Use();
	}
	material->Use(shader);
	shader->SetM(m.m);
	shader->SetCam(GH_PLAYER->CamToWorld());
	shader->SetMVP(mvp.m, mv.m);
	mesh->Draw();
  }
}

Vector3 Object::Forward() const {
  return -(Matrix4::RotZ(euler.z) * Matrix4::RotX(euler.x) * Matrix4::RotY(euler.y)).ZAxis();
}

Matrix4 Object::LocalToWorld() const {
  return Matrix4::Trans(pos) * Matrix4::RotY(euler.y) * Matrix4::RotX(euler.x) * Matrix4::RotZ(euler.z) * Matrix4::Scale(scale * p_scale);
}

Matrix4 Object::WorldToLocal() const {
  return Matrix4::Scale(1.0f / (scale * p_scale)) * Matrix4::RotZ(-euler.z) * Matrix4::RotX(-euler.x) * Matrix4::RotY(-euler.y) * Matrix4::Trans(-pos);
}

void Object::DebugDraw(const Camera& cam) {
  if (mesh) {
    mesh->DebugDraw(cam, LocalToWorld());
  }
}
