#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Church : public Object
{
public:
	Church()
	{
		mesh = AquireMesh("Church.obj");
		shader = LoadLightAdaptedShader();
		texture = AquireTexture("white.bmp");
		scale = Vector3(1e-2f);
	}
	virtual ~Church() {}
};