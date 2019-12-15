#include "HumbugEngine/Animation.h"
#include "HumbugEngine/Timer.h"

#include <iostream>

Animation::Animation()
{
	m_keys = std::vector<std::shared_ptr<AnimationKey>>();
	loop = false;
	smooth = false;
	speed = 1.0f;
}

bool Animation::canRun()
{
	return m_keys.size() > 0;
}

float Animation::getValue(float time)
{
	// First Process
	if (!canRun()) return 0;
	if (loop && m_keys.size() > 1)
	{
		float tMinimalValue = m_keys[0]->getTimeStamp();
		if (time > tMinimalValue)
		{
			float kDuration = (*m_keys.rbegin())->getTimeStamp() - tMinimalValue;
			time -= kDuration * (int)((time - tMinimalValue) / kDuration);
		}
	}

	// Odd Cases
	if (time <= (*m_keys.begin())->getTimeStamp())
		return (*m_keys.begin())->getValue();
	else if (time >= (*m_keys.rbegin())->getTimeStamp())
		return (*m_keys.rbegin())->getValue();
	
	// Process Function
	for (int ii = 0; ii < m_funcs.size(); ii++)
		if (time < m_funcs[ii]->getEndKey()->getTimeStamp()
			&& time > m_funcs[ii]->getStartKey()->getTimeStamp())
			return m_funcs[ii]->getValue(time, smooth);
}

bool Animation::AddKey(float time, float value, bool disableComputeByForce)
{
	for (auto key : m_keys)
		if (key->getTimeStamp() == time)
			return false;
	
	auto newKey = std::make_shared<AnimationKey>(time, value);
	if (m_keys.empty())
	{
		m_keys.push_back(newKey);
	}
	else
	{
		for (int ii = 0; ii < m_keys.size(); ii++)
		{
			if (m_keys[ii]->getTimeStamp() > time)
			{
				m_keys.insert(m_keys.begin() + ii, newKey);
				break;
			}
			if (ii == m_keys.size() - 1)
			{
				m_keys.push_back(newKey);
				break;
			}
		}
	}
	if (!disableComputeByForce)
		Compute();
	return true;
}

void Animation::Compute()
{
	m_funcs.clear();
	for (int ii = 0; ii < m_keys.size() - 1; ii++)
		m_funcs.push_back(std::make_shared<Function>(m_keys[ii], m_keys[ii + 1]));
}