#pragma once
#include "HumbugEngine/Vector.h"
#include "HumbugEngine/Shader.h"
#include <string>
#include <iostream>

class Material
{
public:
	Material(std::string _name = "__Default", Vector3 Ka = Vector3(0.5f), Vector3 Kd = Vector3(0.5f), Vector3 Ks = Vector3(0.8f), float Ns = 32.0f)
		: name(_name), ambient(Ka), diffuse(Kd), specular(Ks), shininess(Ns)
	{}
	Material(Vector3 Ambient = Vector3(0.5f, 0.5f, 0.5f), Vector3 Diffuse = Vector3(0.5, 0.5f, 0.5f), Vector3 Specular = Vector3(0.8f, 0.8f, 0.8f), float Shininess = 32.0f)
		: name("__Default"), ambient(Ambient), diffuse(Diffuse), specular(Specular), shininess(Shininess)
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

	void Use(std::shared_ptr<Shader> & shader)
	{
		glUniform3f(glGetUniformLocation(shader->GetProgId(), "material.ambient"), ambient.x, ambient.y, ambient.z);
		glUniform3f(glGetUniformLocation(shader->GetProgId(), "material.diffuse"), diffuse.x, diffuse.y, diffuse.z);
		glUniform3f(glGetUniformLocation(shader->GetProgId(), "material.specular"), specular.x, specular.y, specular.z);
		glUniform1f(glGetUniformLocation(shader->GetProgId(), "material.shininess"), shininess);
	}
};