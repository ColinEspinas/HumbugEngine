#pragma once
#include "HumbugEngine/Components/Light.h"
#include "HumbugEngine/Components/PointLight.h"
#include "HumbugEngine/Components/DirLight.h"
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Ressources/Shader.h"
#include "HumbugEngine/Utils/Resources.h"
#include <vector>

class Lighting
{
public:
	Lighting(std::vector<std::shared_ptr<Light>> & vLights);
	~Lighting();

	void RenderAllLights(std::vector<std::shared_ptr<Object>> vObjects);
	void RenderLights(std::shared_ptr<Object> Object);
	void RenderDepthMap();

	size_t getLightsCount() { return m_Lights.size(); };
	size_t getPointLightsCount();
	size_t getDirLightsCount();

private:
	std::vector<std::shared_ptr<Light>> & m_Lights;
	//std::shared_ptr<Shader> shadowShader = AquireShader("");
};
typedef std::vector<std::shared_ptr<Light>> PLightVec;
