#pragma once
#include "HumbugEngine/Utils/Vector.h"
#include "HumbugEngine/Ressources/Ressource.h"
#include <cassert>

class Sphere : public Ressource {
public:
  Sphere(float r=1.0f) : center(0.0f), radius(r), Ressource("Sphere","") {}
  Sphere(const Vector3& pos, float r) : center(pos), radius(r), Ressource("Sphere","") {}

  //Transformations to and frpom sphere coordinates
  Matrix4 UnitToLocal() const {
    assert(radius > 0.0f);
    return Matrix4::Trans(center) * Matrix4::Scale(radius);
  }
  Matrix4 LocalToUnit() const {
    assert(radius > 0.0f);
    return Matrix4::Scale(1.0f / radius) * Matrix4::Trans(-center);
  }

  Vector3 center;
  float radius;
  
  void Use() override {}
private:
  void _Load(std::string _path) override {}
};
