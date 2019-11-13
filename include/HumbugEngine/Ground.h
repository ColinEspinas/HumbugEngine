#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Ground : public Object {
public:
  Ground(bool slope=false) {
    std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
    if (slope) {
      MR->AddMesh(AquireMesh("ground_slope.obj"));
    } else {
      MR->AddMesh(AquireMesh("ground.obj"));
    }
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("checker_green.bmp");
		AddComponent(MR);
    m_scale = Vector3(10, 1, 10);
  }
  virtual ~Ground() {}
};
