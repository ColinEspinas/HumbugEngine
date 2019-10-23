#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Portal.h"
#include "HumbugEngine/Player.h"
#include "HumbugEngine/Lighting.h"

class Scene {
public:
  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player)=0;
  virtual void Unload() {};
};
