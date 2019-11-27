#pragma once
#include "HumbugEngine/Light.h"
class PointLight :
	public Light
{
public:
	PointLight(
		Vector3 Position,
		float constant,
		float linear,
		float quadratic,
		Vector3 Ambient = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 Diffuse = Vector3(1.0f, 0.8f, 0.8f),
		Vector3 Specular = Vector3(0.5f, 0.5f, 0.5f)
	);
	~PointLight() { --m_Count; };

	void Use(std::shared_ptr<Shader> & objectShader) override;
	void UseAt(std::shared_ptr<Shader> & objectShader, Vector3 pos) override;
	static unsigned int getCount() { return m_Count; }

	bool isVisibleFrom(Vector3 pos) const override;

	void MoveTo(Vector3 newPos);

private:
	float m_Constant;
	float m_Linear;
	float m_Quadratic;

	static unsigned int m_Count;
};
