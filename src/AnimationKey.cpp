#include "HumbugEngine/AnimationKey.h"

AnimationKey::AnimationKey(float timeStamp, float value) {
	m_key[0] = timeStamp;
	m_key[1] = value;
}
float AnimationKey::getTimeStamp() {
	return m_key[0];
}
float AnimationKey::getValue() {
	return m_key[1];
}
void AnimationKey::setTimeStamp(float timeStamp) {
	m_key[0] = timeStamp;
}
void AnimationKey::setValue(float value) {
	m_key[1] = value;
}
std::vector<float> AnimationKey::get() {
	return m_key;
}
void AnimationKey::set(float timeStamp, float value) {
	m_key[0] = timeStamp;
	m_key[1] = value;
}
