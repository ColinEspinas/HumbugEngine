#pragma once
#include "HumbugEngine/Scene.h"

class Level6 : public Scene {
public:
  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player) override;
};
