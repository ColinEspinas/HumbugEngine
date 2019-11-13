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
    std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
    if (type == SCALE) {
      MR->AddMesh(AquireMesh("tunnel_scale.obj"));
    } else if (type == SLOPE) {
      MR->AddMesh(AquireMesh("tunnel_slope.obj"));
    } else {
      MR->AddMesh(AquireMesh("tunnel.obj"));
    }
    MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("checker_gray.bmp");
		AddComponent(MR);
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
