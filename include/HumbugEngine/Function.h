#pragma once
#include "HumbugEngine/AnimationKey.h"
#include <memory>
#include <array>

class Function
{
public:
	Function(std::shared_ptr<AnimationKey> key1, std::shared_ptr<AnimationKey> key2);
	float getValue(float time, bool smooth = true);

	std::shared_ptr<AnimationKey> getStartKey();
	std::shared_ptr<AnimationKey> getEndKey();

private:
	std::shared_ptr<AnimationKey> startKey, endKey;
	std::array<float, 4> m_coeffs;
};