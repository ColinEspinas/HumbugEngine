#pragma once
#include "HumbugEngine/Core/Scene.h"

class Level2 : public Scene {
public:
  Level2(int rooms) : num_rooms(rooms) {}

  virtual void Load(Player& player) override;

private:
  int num_rooms;
};
