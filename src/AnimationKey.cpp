#include "HumbugEngine/AnimationKey.h"

AnimationKey::AnimationKey(float timeStamp, float value) {
	m_time = timeStamp;
	m_value = value;
}

float AnimationKey::getTimeStamp() {
	return m_time;
}

float AnimationKey::getValue() {
	return m_value;
}

void AnimationKey::setTimeStamp(float timeStamp) {
	m_time = timeStamp;
}

void AnimationKey::setValue(float value) {
	m_value = value;
}

void AnimationKey::set(float timeStamp, float value) {
	m_time = timeStamp;
	m_value = value;
}
