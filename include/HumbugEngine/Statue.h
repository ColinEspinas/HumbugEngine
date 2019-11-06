#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Statue : public Object {
public:
  Statue(const char* model) {
    mesh = AquireMesh(model);
    shader = AquireShader("texture");
    texture = AquireTexture("gold.bmp");
  }
  virtual ~Statue() {}
};
