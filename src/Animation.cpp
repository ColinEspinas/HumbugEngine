#include "HumbugEngine/Animation.h"

Animation::Animation() {
	m_loop = false;
	m_smooth = true;
	m_kspeed = 1.0f;
}


void Animation::CreateKeyAnim() {
	m_keys.push_back(AnimationKey(1.0f, 10.0f));
	m_keys.push_back(AnimationKey(2.0f, 20.0f));
	m_keys.push_back(AnimationKey(3.0f, 30.0f));
	m_keys.push_back(AnimationKey(4.0f, 40.0f));
}

AnimationKey Animation::getKey(int i) {
	return m_keys[i];
}