#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Pillar : public Object {
public:
  Pillar() {
    mesh = AquireMesh("pillar.obj");
    shader = AquireShader("texture");
    texture = AquireTexture("white.bmp");
    m_scale = Vector3(0.1f);
  }
  virtual ~Pillar() {}
};
