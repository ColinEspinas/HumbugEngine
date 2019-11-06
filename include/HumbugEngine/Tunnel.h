#pragma once
#include "HumbugEngine/Objects/Object.h"

class Tunnel : public Object {
public:
  enum Type {
    NORMAL = 0,
    SCALE = 1,
    SLOPE = 2,
  };

  Tunnel(Type type) : type(type) {
    if (type == SCALE) {
      mesh = AquireMesh("tunnel_scale.obj");
    } else if (type == SLOPE) {
      mesh = AquireMesh("tunnel_slope.obj");
    } else {
      mesh = AquireMesh("tunnel.obj");
    }
    shader = AquireShader("texture");
    texture = AquireTexture("checker_gray.bmp");
  }
  virtual ~Tunnel() {}

  void SetDoor1(Object& portal) const {
    portal.m_pos = LocalToWorld().MulPoint(Vector3(0, 1, 1));
    portal.m_euler = m_euler;
    portal.m_scale = Vector3(0.6f, 0.999f, 1) * m_scale.x;
  }
  void SetDoor2(Object& portal) const {
    portal.m_euler = m_euler;
    if (type == SCALE) {
      portal.m_pos = LocalToWorld().MulPoint(Vector3(0, 0.5f, -1));
      portal.m_scale = Vector3(0.3f, 0.499f, 0.5f) * m_scale.x;
    } else if (type == SLOPE) {
      portal.m_pos = LocalToWorld().MulPoint(Vector3(0, -1, -1));
      portal.m_scale = Vector3(0.6f, 0.999f, 1) * m_scale.x;
    } else {
      portal.m_pos = LocalToWorld().MulPoint(Vector3(0, 1, -1));
      portal.m_scale = Vector3(0.6f, 0.999f, 1) * m_scale.x;
    }
  }

private:
  Type type;
};
