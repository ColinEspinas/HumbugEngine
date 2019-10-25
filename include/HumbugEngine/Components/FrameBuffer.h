#pragma once
#include "HumbugEngine/Components/Camera.h"
#include <GL/glew.h>

//Forward declaration
class Portal;

class FrameBuffer : public Component {
public:
  FrameBuffer();

  void Render(const Camera& cam, GLuint curFBO, const Portal* skipPortal);
  int Use() override;

private:
  GLuint texId;
  GLuint fbo;
  GLuint renderBuf;
};
