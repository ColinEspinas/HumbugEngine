#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Cat : public Object
{
public:
	Cat()
	{
		mesh = AquireMesh("cat.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		scale = Vector3(1e-2f);
	}
	virtual ~Cat() {}
};