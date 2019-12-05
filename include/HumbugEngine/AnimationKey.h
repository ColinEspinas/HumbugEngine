#pragma once
#include <vector>

class AnimationKey {
private:
	std::vector<float> m_key = std::vector<float>(2);
public:
	AnimationKey(float timeStamp,float value);
	float getTimeStamp();
	float getValue();
	void setTimeStamp(float timeStamp);
	void setValue(float value);
	std::vector<float> get();
	void set(float timeStamp, float value);


};