#include "HumbugEngine/Components/DirLight.h"
#include <string>

unsigned int DirLight::m_Count = 0;

DirLight::DirLight(Vector3 Direction, Vector3 Ambient, Vector3 Diffuse, Vector3 Specular)
	: m_Direction(Direction), Light("DirLight")
{
	m_Ambient = Ambient;
	m_Diffuse = Diffuse;
	m_Specular = Specular;
	m_Id = m_Count;
	++m_Count;
}

void DirLight::Use(std::shared_ptr<Shader>& objectShader)
{
	std::string IdString = std::string("dirLights[" + std::to_string(m_Id) + "]");
	glUniform1i(glGetUniformLocation(objectShader->GetProgId(), "dirLightsCount"), getCount());
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".direction").c_str()), m_Position.x, m_Position.y, m_Position.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".ambient").c_str()), m_Ambient.x, m_Ambient.y, m_Ambient.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".diffuse").c_str()), m_Diffuse.x, m_Diffuse.y, m_Diffuse.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), std::string(IdString + ".specular").c_str()), m_Specular.x, m_Specular.y, m_Specular.z);
}
