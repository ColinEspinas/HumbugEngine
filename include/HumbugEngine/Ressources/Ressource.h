#pragma once
#include <string>

class Ressource
{
protected:
	std::string m_name;
	std::string m_pathSource;

	virtual void _Load(std::string _path) = 0;

public:
	Ressource(std::string _name, std::string _path);

	std::string getName() const;
	std::string getPath() const;

	void Load(std::string newPath = "", bool UseOnLoad = true);
	virtual void Use() = 0;
};