#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Animation.h"
#include "HumbugEngine/GameHeader.h"
#include "HumbugEngine/Timer.h"
#include <vector>
#include <array>


namespace AnimationType
{
	enum METHOD
	{
		TRANSLATION = 0,
		ROTATION = 1,
		SCALE = 2
	};

	enum AXIS
	{
		X = 0,
		Y = 1,
		Z = 2
	};
}


class Animator {
private:
	float localTimer;
	int index;
	std::array<std::array<std::shared_ptr<Animation>,3>,3> m_lstAnim;
	Object* m_target;

public:
	Animator(Object* obj, int id = 0);
	void Update();

	void Build(std::vector<std::pair<std::array<int,2>,std::vector<std::array<float,2>>>> content);

	std::shared_ptr<Animation> getAnimation(AnimationType::METHOD _m, AnimationType::AXIS _a);
	void LoopAll(bool state = true);
};