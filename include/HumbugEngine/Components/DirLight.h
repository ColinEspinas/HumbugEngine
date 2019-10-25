#pragma once
#include "HumbugEngine/Components/Light.h"

class DirLight : public Light
{
public:
	DirLight(
		Vector3 Direction,
		Vector3 Ambient = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 Diffuse = Vector3(1.0f, 0.8f, 0.8f),
		Vector3 Specular = Vector3(0.5f, 0.5f, 0.5f)
	);
	~DirLight() { --m_Count; };

	void Use(std::shared_ptr<Shader> & objectShader) override;
	static unsigned int getCount() { return m_Count; }

private:
	Vector3 m_Direction;

	static unsigned int m_Count;
};
