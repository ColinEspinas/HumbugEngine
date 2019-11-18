#pragma once
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Utils/Vector.h"

class Sky {
public:
  Sky() {
    mesh = AquireMesh("quad.obj");
    shader = AquireShader("sky");
  }

  void Draw(const Camera& cam) {
    glDepthMask(GL_FALSE);
    const Matrix4 mvp = cam.projection.Inverse();
    const Matrix4 mv = cam.worldView.Inverse();
	//std::cout << (shader == nullptr) << std::endl; // DEBUG
    shader->Use();
    shader->SetMVP(mvp.m, mv.m);
    mesh->Draw();
    glDepthMask(GL_TRUE);
  }

private:
  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Shader> shader;
};
