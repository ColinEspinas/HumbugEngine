#pragma once
#include "..\..\Object.h"
#include "..\..\Resources.h"

class Plant : public Object
{
public:
	Plant()
	{
		mesh = AquireMesh("Plant.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		scale = Vector3(1e-1f);
	}
	virtual ~Plant() {}
};