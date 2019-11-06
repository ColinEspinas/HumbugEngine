#pragma once
#include "HumbugEngine/Utils/GameHeader.h"
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Components/FrameBuffer.h"
#include "HumbugEngine/Components/MeshRenderer.h"
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Ressources/Shader.h"
#include <memory>

class Portal : public Object {
protected:
  bool allowForComponents() override { return false; }

public:
  //Subclass that represents a warp
  struct Warp {
    Warp(const Portal* fromPortal) : fromPortal(fromPortal), toPortal(nullptr) {
      delta.MakeIdentity();
      deltaInv.MakeIdentity();
    }

    Matrix4 delta;
    Matrix4 deltaInv;
    const Portal* fromPortal;
    const Portal* toPortal;
  };

  Portal();
  virtual ~Portal() {}

  virtual void Draw(const Camera& cam, GLuint curFBO) override;
  void DrawPink(const Camera& cam);

  Vector3 GetBump(const Vector3& a) const;
  const Warp* Intersects(const Vector3& a, const Vector3& b, const Vector3& bump) const;
  float DistTo(const Vector3& pt) const;

  static void Connect(std::shared_ptr<Portal>& a, std::shared_ptr<Portal>& b);
  static void Connect(Warp& a, Warp& b);

  Warp front;
  Warp back;

  void DebugDraw(const Camera& cam, const Matrix4& mat);

private:
  std::shared_ptr<Shader> m_errShader, m_shader;
  FrameBuffer m_frameBuf[GH_MAX_RECURSION <= 1 ? 1 : GH_MAX_RECURSION - 1];

  std::shared_ptr<MeshRenderer> m_portalFrame;
};
typedef std::vector<std::shared_ptr<Portal>> PPortalVec;