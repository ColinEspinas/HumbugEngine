#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Pillar : public Object {
public:
  Pillar() {
    std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("pillar.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("white.bmp");
		AddComponent(MR);
    m_scale = Vector3(0.1f);
  }
  virtual ~Pillar() {}
};
