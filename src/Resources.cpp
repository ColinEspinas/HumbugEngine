#include "HumbugEngine/Resources.h"
#include <unordered_map>

std::shared_ptr<Mesh> AquireMesh(const char* name) {
  static std::unordered_map<std::string, std::weak_ptr<Mesh>> map;
  std::weak_ptr<Mesh>& mesh = map[std::string(name)];
  if (mesh.expired()) {
    std::shared_ptr<Mesh> newMesh(std::make_shared<Mesh>(name));
    mesh = newMesh;
    return newMesh;
  } else {
    return mesh.lock();
  }
}

std::shared_ptr<Shader> AquireShader(const char* name) {
  static std::unordered_map<std::string, std::weak_ptr<Shader>> map;
  std::weak_ptr<Shader>& shader = map[std::string(name)];
  if (shader.expired()) {
    std::shared_ptr<Shader> newShader(std::make_shared<Shader>(name));
    shader = newShader;
    return newShader;
  } else {
    return shader.lock();
  }
}

std::shared_ptr<Texture> AquireTexture(const char* name, int rows, int cols) {
  static std::unordered_map<std::string, std::weak_ptr<Texture>> map;
  std::weak_ptr<Texture>& tex = map[std::string(name)];
  if (tex.expired()) {
    std::shared_ptr<Texture> newTex(std::make_shared<Texture>(name, rows, cols));
    tex = newTex;
    return newTex;
  } else {
    return tex.lock();
  }
}

std::shared_ptr<UIPattern> AquirePattern(const char* name) {
  static std::unordered_map<std::string, std::weak_ptr<UIPattern>> map;
  std::weak_ptr<UIPattern>& pattern = map[std::string(name)];
  if (pattern.expired()) {
    std::shared_ptr<UIPattern> newPattern(std::make_shared<UIPattern>(std::string(name)));
    pattern = newPattern;
    return newPattern;
  } else {
    return pattern.lock();
  }
}
