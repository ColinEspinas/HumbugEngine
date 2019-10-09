#pragma once
#include "..\Entity.h"

class BallPhysic : public PhysicRuleset
{
public:

	BallPhysic(Entity* phy = nullptr);

	virtual void PerReset() override;
	virtual void PerFrame() override;
	virtual Vector3 PerHit(Object& other, const Vector3& push) override;

private:

	bool onGround;
	float curFriction;

	void Move(float h, float v);
};