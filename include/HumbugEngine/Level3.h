#pragma once
#include "HumbugEngine/Scene.h"

class Level3 : public Scene {
public:
  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player) override;
};
