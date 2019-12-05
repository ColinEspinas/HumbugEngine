#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class TestObj : public Object
{
public:
	TestObj(std::string obj, float _scale = 1.0f, std::string _texture = "White.bmp")
	{
		mesh = AquireMesh(obj.c_str());
		shader = LoadLightAdaptedShader();
		texture = AquireTexture(_texture.c_str());
		scale = Vector3(_scale);
	}
	virtual ~TestObj() {}
};