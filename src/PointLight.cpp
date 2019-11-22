#include "HumbugEngine/PointLight.h"
#include <string>
#include <math.h>

unsigned int PointLight::m_Count = 0;

PointLight::PointLight(Vector3 Position, float Constant, float Linear, float Quadratic, Vector3 Ambient, Vector3 Diffuse, Vector3 Specular)
	: m_Constant(Constant), m_Linear(Linear), m_Quadratic(Quadratic)
{
	m_Position = Position;
	m_Ambient = Ambient;
	m_Diffuse = Diffuse;
	m_Specular = Specular;
	m_Id = m_Count;
	++m_Count;
}

void PointLight::Use(std::shared_ptr<Shader>& objectShader)
{
	std::string IdString = std::string("pointLights[" + std::to_string(m_Id) + "]");
	glUniform1i(glGetUniformLocation(objectShader->GetProgId(), "pointLightsCount"), getCount());
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".position").c_str()), m_Position.x, m_Position.y, m_Position.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".ambient").c_str()), m_Ambient.x, m_Ambient.y, m_Ambient.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".diffuse").c_str()), m_Diffuse.x, m_Diffuse.y, m_Diffuse.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".specular").c_str()), m_Specular.x, m_Specular.y, m_Specular.z);
	glUniform1f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".constant").c_str()), m_Constant);
	glUniform1f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".linear").c_str()), m_Linear);
	glUniform1f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".quadratic").c_str()), m_Quadratic);

	// TO CHANGE AS SOON AS POSSIBLE
	if (!this->On) glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".position").c_str()), 100, -100, 100);
}

bool PointLight::isVisibleFrom(Vector3 pos) const
{
	float d = (pos - m_Position).Mag();
	return (m_Quadratic * d * d + m_Linear * d + m_Constant > GH_MIN_LIGHT_INTENSITY);
}

void PointLight::MoveTo(Vector3 newPos)
{
	this->m_Position = newPos;
}
