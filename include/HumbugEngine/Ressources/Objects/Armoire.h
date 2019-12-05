#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"

class Armoire : public Object
{
public:
	Armoire(std::string obj, float _scale = 1.0f ,std::string _texture = "White.bmp")
	{
		mesh = AquireMesh(obj.c_str());
		shader = AquireShader("texture");
		texture = AquireTexture(_texture.c_str());
		scale = Vector3(_scale);
	}
	virtual ~Armoire() {}
};