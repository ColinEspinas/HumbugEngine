#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Plant : public Object
{
public:
	Plant()
	{
		mesh = AquireMesh("Plant.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		m_scale = Vector3(1e-1f);
	}
	virtual ~Plant() {}
};