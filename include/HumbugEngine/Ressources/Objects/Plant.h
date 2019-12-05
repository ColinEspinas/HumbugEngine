#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Plant : public Object
{
public:
	Plant()
	{
		mesh = AquireMesh("Plant.obj");
		shader = LoadLightAdaptedShader();
		texture = AquireTexture("white.bmp");
		scale = Vector3(1e-1f);
	}
	virtual ~Plant() {}
};