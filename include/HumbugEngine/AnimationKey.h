#pragma once
#include <vector>

class AnimationKey {
private:
	float m_value;
	float m_time;

public:
	AnimationKey(float timeStamp, float value);
	float getTimeStamp();
	float getValue();
	void setTimeStamp(float timeStamp);
	void setValue(float value);
	void set(float timeStamp, float value);


};