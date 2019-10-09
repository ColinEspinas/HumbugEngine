#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Shader.h"

class Light
{
public:
	Light() {};
	~Light() {};

	virtual void Use(std::shared_ptr<Shader> & objectShader) = 0;

	bool On = true;

protected:
	Vector3 m_Position;
	Vector3 m_Ambient;
	Vector3 m_Diffuse;
	Vector3 m_Specular;

	unsigned int m_Id;
};

