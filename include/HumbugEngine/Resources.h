#pragma once
#include "HumbugEngine/Mesh.h"
#include "HumbugEngine/Texture.h"
#include "HumbugEngine/Shader.h"
#include "HumbugEngine/UIPattern.h"
#include <memory>

std::shared_ptr<Mesh> AquireMesh(const char* name);
std::shared_ptr<Shader> AquireShader(const char* name);
std::shared_ptr<Texture> AquireTexture(const char* name, int rows=1, int cols=1);

std::shared_ptr<UIPattern> AquirePattern(const char* name);
