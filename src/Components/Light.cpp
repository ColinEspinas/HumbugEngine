#include "HumbugEngine/Components/Light.h"

void Light::Use(std::shared_ptr<Shader> & objectShader)
{
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), "light.position"), m_Position.x, m_Position.y, m_Position.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), "light.ambient"), m_Ambient.x, m_Ambient.y, m_Ambient.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), "light.diffuse"), m_Diffuse.x, m_Diffuse.y, m_Diffuse.z);
	glUniform3f(glGetUniformLocation(objectShader->GetProgId(), "light.specular"), m_Specular.x, m_Specular.y, m_Specular.z);
}
