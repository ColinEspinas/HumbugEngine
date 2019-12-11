#pragma once
#include "HumbugEngine/Function.h"
#include "HumbugEngine/GameHeader.h"
#include <memory>


class Animation
{
public:
	Animation();
	float getValue(float time);
	bool canRun();

	bool AddKey(float time, float value, bool disableComputeByForce = false);

	bool loop;
	bool smooth;
	float speed;

private:
	std::vector<std::shared_ptr<AnimationKey>> m_keys;

	void Compute();
	std::vector<std::shared_ptr<Function>> m_funcs;
};