#include "HumbugEngine/Ressources/Ressource.h"

// Constructor
Ressource::Ressource(std::string _name, std::string _path)
	: m_name(_name), m_pathSource(_path)
{}

// Load Ressource from Path File
void Ressource::Load(std::string newPath, bool UseOnLoad)
{
	if (newPath.empty())
		this->_Load(this->m_name);
	else this->_Load(newPath);
	if (UseOnLoad)
		this->Use();
}

// Return Name
std::string Ressource::getName() const
{
	return m_name;
}

// Return Path
std::string Ressource::getPath() const
{
	return m_pathSource;
}