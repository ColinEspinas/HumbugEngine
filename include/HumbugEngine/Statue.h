#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Statue : public Object {
public:
  Statue(const char* model) {
    std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh(model));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("gold.bmp");
		AddComponent(MR);
  }
  virtual ~Statue() {}
};
