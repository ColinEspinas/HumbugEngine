#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Statue : public Object {
public:
  Statue(const char* model) {
    mesh = AquireMesh(model);
    shader = LoadLightAdaptedShader();
    texture = AquireTexture("gold.bmp");
  }
  virtual ~Statue() {}
};
