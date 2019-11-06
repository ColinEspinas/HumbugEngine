#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class PillarRoom : public Object {
public:
  PillarRoom() {
    mesh = AquireMesh("pillar_room.obj");
    shader = AquireShader("texture");
    texture = AquireTexture("three_room.bmp");
    m_scale = Vector3(1.1f);
  }

  void SetPortal(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(0, 1.5f, -1));
    portal.m_euler = m_euler;
    portal.m_euler.y -= GH_PI / 2;
    portal.m_scale = Vector3(1, 1.5f, 1) * m_scale;
  }
  virtual ~PillarRoom() {}
};