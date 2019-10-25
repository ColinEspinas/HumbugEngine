#pragma once
#include "HumbugEngine/Ressources/Ressource.h"
#include "HumbugEngine/Ressources/Shader.h"

#include "HumbugEngine/Utils/Vector.h"
#include <string>
#include <iostream>

class Material : public Ressource
{
private:
	std::shared_ptr<Shader> m_shader;

	void _Load(std::string _path) override {}

public:
	Material(std::string _name = "__Default", Vector3 Ka = Vector3(0.5f), Vector3 Kd = Vector3(0.5f), Vector3 Ks = Vector3(0.8f), float Ns = 32.0f)
		: name(_name), ambient(Ka), diffuse(Kd), specular(Ks), shininess(Ns)
		, Ressource("Material", "")
	{}
	Material(Vector3 Ambient = Vector3(0.5f, 0.5f, 0.5f), Vector3 Diffuse = Vector3(0.5, 0.5f, 0.5f), Vector3 Specular = Vector3(0.8f, 0.8f, 0.8f), float Shininess = 32.0f)
		: name("__Default"), ambient(Ambient), diffuse(Diffuse), specular(Specular), shininess(Shininess)
		, Ressource("Material", "")
	{}

	std::string name;

	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	float shininess;

	Material lookFor(std::string _name)
	{
		if (name == _name)
			return *this;
		return Material("_Error");
	}
	bool isError()
	{
		return (this->name == "_Error");
	}

	void SetMaterial()
	{
		// TODO
	}

	//DEBUG
	void Print()
	{
		std::cout << name << '\n';
		std::cout << ambient.x << ' ' << ambient.y << ' ' << ambient.z << '\n';
		std::cout << diffuse.x << ' ' << diffuse.y << ' ' << diffuse.z << '\n';
		std::cout << specular.x << ' ' << specular.y << ' ' << specular.z << '\n';
		std::cout << shininess << '\n';
	}

	void Bind(std::shared_ptr<Shader> & shader)
	{
		if (shader)
			m_shader = shader;
	}

	void Use() override
	{
		if (m_shader == nullptr)
			return;
		glUniform3f(glGetUniformLocation(m_shader->GetProgId(), "material.ambient"), ambient.x, ambient.y, ambient.z);
		glUniform3f(glGetUniformLocation(m_shader->GetProgId(), "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(glGetUniformLocation(m_shader->GetProgId(), "material.specular"), specular.x, specular.y, specular.z);
		glUniform1f(glGetUniformLocation(m_shader->GetProgId(), "material.shininess"), shininess);
	}
};