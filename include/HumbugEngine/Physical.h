#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Portal.h"
#include "HumbugEngine/Sphere.h"

class Physical : public Object {
public:
  Physical();
  virtual ~Physical() override {}

  virtual void Reset() override;
  virtual void Update() override;
  virtual void OnCollide(Object& other, const Vector3& push);

  void SetPosition(const Vector3& _pos) {
    m_pos = _pos;
    prev_pos = _pos;
  }

  bool TryPortal(const Portal& portal);

  virtual Physical* AsPhysical() { return this; }

  Vector3 gravity;
  Vector3 velocity;
  float bounce;
  float friction;
  float high_friction;
  float drag;
  
  Vector3 prev_pos;

  std::vector<Sphere> hitSpheres;
};
