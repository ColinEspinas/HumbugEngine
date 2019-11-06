#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Objects/Portal.h"
#include "HumbugEngine/Objects/Player.h"
#include "HumbugEngine/Core/Lighting.h"

class Scene {
private:
  PObjectVec m_Objects;

protected:
  void AddObject(std::shared_ptr<Object> Obj);
  void RemoveObject(std::shared_ptr<Object> Obj);
  std::shared_ptr<Object> GetObject(int index);
  int GetObjectAmount();

public:
  Scene();
  
  virtual void Load(Player& player)=0;
  virtual void Unload() {}
};
