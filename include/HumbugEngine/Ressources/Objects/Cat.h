#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class Cat : public Object
{
public:
	Cat()
	{
		mesh = AquireMesh("cat.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		m_scale = Vector3(1e-2f);
	}
	virtual ~Cat() {}
};