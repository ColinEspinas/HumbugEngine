#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"

class TestObj : public Object
{
public:
	TestObj(std::string obj, float _scale = 1.0f, std::string _texture = "White.bmp")
	{
		mesh = AquireMesh(obj.c_str());
		shader = AquireShader("texture");
		texture = AquireTexture(_texture.c_str());
		m_scale = Vector3(_scale);
	}
	virtual ~TestObj() {}
};