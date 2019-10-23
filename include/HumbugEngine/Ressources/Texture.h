#pragma once
#include "HumbugEngine/Ressources/Ressource.h"
#include <GL/glew.h>

class Texture : public Ressource {
public:
  Texture(std::string fname, int rows, int cols);

  void Use() override;

private:
  GLuint texId;
  bool is3D;

  void _Load(std::string _path) override;
};
