#pragma once
#include "HumbugEngine/Ressources/Mesh.h"
#include "HumbugEngine/Ressources/Texture.h"
#include "HumbugEngine/Ressources/Shader.h"
#include <memory>

std::shared_ptr<Mesh> AquireMesh(const char* name);
std::shared_ptr<Shader> AquireShader(const char* name);
std::shared_ptr<Texture> AquireTexture(const char* name, int rows=1, int cols=1);
