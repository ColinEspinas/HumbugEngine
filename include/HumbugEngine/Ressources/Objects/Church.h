#pragma once
#include "..\..\Object.h"
#include "..\..\Resources.h"

class Church : public Object
{
public:
	Church()
	{
		mesh = AquireMesh("Church.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("white.bmp");
		scale = Vector3(1e-2f);
	}
	virtual ~Church() {}
};