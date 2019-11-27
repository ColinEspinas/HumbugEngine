#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Shader.h"
#include <limits>

class Light
{
public:
	Light() {};
	~Light() {};

	virtual void Use(std::shared_ptr<Shader> & objectShader) = 0;

	bool On = true;

	virtual bool isVisibleFrom(Vector3 pos) const { return true; }

	Vector3 getPosition() const { return m_Position; }
	virtual void UseAt(std::shared_ptr<Shader> & objectShader, Vector3 pos) { Use(objectShader); }

protected:
	Vector3 m_Position;
	Vector3 m_Ambient;
	Vector3 m_Diffuse;
	Vector3 m_Specular;

	unsigned int m_Id;
};

