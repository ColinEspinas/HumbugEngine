#pragma once
#include "..\..\Scene.h"

class Level_1 : public Scene
{
public:
	virtual void Load(PObjectVec& objs, PLightVec& lights, PPortalVec& portals, Player& player) override;
};