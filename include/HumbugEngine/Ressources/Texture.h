#pragma once
#include "HumbugEngine/Ressources/Ressource.h"
#include <GL/glew.h>

class Texture : public Ressource {
public:
  Texture(std::string fname, int rows, int cols);

  void Use() override;

private:
  GLuint m_texId;
  bool m_is3D;

  int m_rows, m_cols;

  void _Load(std::string _path) override;
};
