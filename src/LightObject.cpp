#include "HumbugEngine/Objects/LightObject.h"

// Default Constructor
LightObject::LightObject(bool genLight)
{
	if (genLight)
		AddComponent(std::make_shared<PointLight>(m_pos, 1.0f, 0.1f, 0.05f)); // Default PointLight of LightObject
}