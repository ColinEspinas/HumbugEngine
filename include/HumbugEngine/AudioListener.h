#include <al.h>
#include <alc.h>
#include "HumbugEngine/Object.h"
#include <iostream>

#pragma once
class AudioListener
{
private:
	std::vector<ALfloat> m_orientation;
	Vector3 m_pos;
	Vector3 m_speed;
public:
	AudioListener() {};
	AudioListener(Vector3 pos, Vector3 speed, std::vector<ALfloat> orientation);
	void updateListener(Vector3 pos, Vector3 speed, std::vector<ALfloat> orientation);
};

