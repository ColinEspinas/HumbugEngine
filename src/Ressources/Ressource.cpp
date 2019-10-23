#include "HumbugEngine/Ressources/Ressource.h"

// Constructor
Ressource::Ressource(std::string _name, std::string _path)
	: m_name(_name), m_pathSource(_path)
{}

// Load Ressource from Path File
void Ressource::Load(std::string newPath)
{
	if (newPath.empty())
		this->_Load(this->m_name);
	else this->_Load(newPath);
}