#pragma once
#include "HumbugEngine/Scene.h"

class Level4 : public Scene {
public:
  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player) override;
};
