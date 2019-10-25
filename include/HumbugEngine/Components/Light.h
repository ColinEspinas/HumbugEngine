#pragma once
#include "HumbugEngine/Components/Component.h"
#include "HumbugEngine/Ressources/Shader.h"

class Light : public Component
{
public:
	Light(std::string _name = "Light") : Component(_name) {};
	~Light() {};

	int Use() override {}
	virtual void Use(std::shared_ptr<Shader> & objectShader) = 0;

	bool On = true;

protected:
	Vector3 m_Position;
	Vector3 m_Ambient;
	Vector3 m_Diffuse;
	Vector3 m_Specular;

	unsigned int m_Id;
};

