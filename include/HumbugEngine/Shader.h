#pragma once
#include <GL/glew.h>
#include <vector>
#include "HumbugEngine/Vector.h"

class Shader {
public:
  Shader(const char* name);
  ~Shader();

  void Use();
  void SetM(const float* m);
  void SetMVP(const float* mvp, const float* mv);
  void SetCam(const Matrix4& pos);
  GLuint& GetProgId() { return progId; };

private:
  GLuint LoadShader(const char* fname, GLenum type);

  std::vector<std::string> attribs;
  GLuint vertId;
  GLuint fragId;
  GLuint progId;
  GLuint mvpId;
  GLuint mvId;
  GLuint mId;
  GLuint viewPosId;
};
