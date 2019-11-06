#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Church : public Object
{
public:
	Church()
	{
		mesh = AquireMesh("Church.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		m_scale = Vector3(1e-2f);
	}
	virtual ~Church() {}
};