#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class House : public Object {
public:
  House(const char* tex) {
    mesh = AquireMesh("square_rooms.obj");
    shader = AquireShader("texture");
    texture = AquireTexture(tex);
    m_scale = Vector3(1.0f, 3.0f, 1.0f);
  }
  virtual ~House() {}

  void SetDoor1(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(4.0f, 0.5f, 10.0f));
    portal.m_euler = m_euler;
    portal.m_scale = Vector3(2, 0.5f, 1) * m_scale;
  }
  void SetDoor2(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(10.0f, 0.5f, 4.0f));
    portal.m_euler = m_euler;
    portal.m_euler.y -= GH_PI/2;
    portal.m_scale = Vector3(2, 0.5f, 1) * m_scale;
  }
  void SetDoor3(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(16.0f, 0.5f, 10.0f));
    portal.m_euler = m_euler;
    portal.m_euler.y -= GH_PI;
    portal.m_scale = Vector3(2, 0.5f, 1) * m_scale;
  }
  void SetDoor4(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(10.0f, 0.5f, 16.0f));
    portal.m_euler = m_euler;
    portal.m_euler.y -= GH_PI*3/2;
    portal.m_scale = Vector3(2, 0.5f, 1) * m_scale;
  }
};
