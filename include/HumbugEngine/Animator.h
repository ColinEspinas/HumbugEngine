#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Animation.h"
#include "HumbugEngine/GameHeader.h"
#include "HumbugEngine/Timer.h"
#include <vector>


class Animator {
private:
	//std::vector<Animation> m_lstAnim;
	int index;
	std::vector<std::vector<Animation>> m_lstAnim;
	Timer timer;

public:
	Animator();
	void addTransformAnimation(Animation anim);
	void addRotationAnimation(Animation anim);
	void addScaleAnimation(Animation anim);
	void Update(std::shared_ptr<Object> obj);
};