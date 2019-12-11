#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Portal.h"
#include "HumbugEngine/Player.h"
#include "HumbugEngine/Lighting.h"
#include "HumbugEngine/UIQuad.h"

class Scene {
public:
  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, PQuadVec& quads, Player& player)=0;
  virtual void Unload() {};
};
