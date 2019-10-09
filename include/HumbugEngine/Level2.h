#pragma once
#include "HumbugEngine/Scene.h"

class Level2 : public Scene {
public:
  Level2(int rooms) : num_rooms(rooms) {}

  virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player) override;

private:
  int num_rooms;
};
