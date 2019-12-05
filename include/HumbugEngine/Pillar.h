#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Pillar : public Object {
public:
  Pillar() {
    mesh = AquireMesh("pillar.obj");
    shader = LoadLightAdaptedShader();
    texture = AquireTexture("white.bmp");
    scale = Vector3(0.1f);
  }
  virtual ~Pillar() {}
};
