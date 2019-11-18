#pragma once
#include "HumbugEngine/PhysicRuleset.h"

class Entity : public Physical
{
public:
	Entity(std::shared_ptr<Object>& obj, std::shared_ptr<PhysicRuleset>& pR);
	virtual ~Entity() override {};

	virtual void Reset() override;
	virtual void Update() override;
	virtual void OnCollide(Object& other, const Vector3& push) override;

private:
	std::shared_ptr<PhysicRuleset> physics;
};