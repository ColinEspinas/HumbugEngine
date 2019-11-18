#pragma once
#include "HumbugEngine/Physical.h"
#include "HumbugEngine/Vector.h"

class Entity;

class PhysicRuleset
{
protected:
	Entity* body;

public:
	PhysicRuleset(Entity* phy = nullptr) : body(phy) {}
	void SetBody(Entity* phy) { body = phy; }

	virtual void PerReset() = 0;
	virtual void PerFrame() = 0;
	virtual Vector3 PerHit(Object& other, const Vector3& push) = 0;
};