#pragma once
#include "HumbugEngine/AnimationKey.h"

class Animation {
public:
	Animation();
	void CreateKeyAnim();
	AnimationKey getKey(int i);

private:
	std::vector<AnimationKey> m_keys;
	bool m_loop;
	bool m_smooth;
	float m_kspeed;
};