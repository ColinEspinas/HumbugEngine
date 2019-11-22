#pragma once
#include "HumbugEngine/Light.h"
#include "HumbugEngine/PointLight.h"
#include "HumbugEngine/DirLight.h"
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Shader.h"
#include "HumbugEngine/Resources.h"
#include "HumbugEngine/Portal.h"
#include <vector>

class Lighting
{
public:
	Lighting(std::vector<std::shared_ptr<Light>> & vLights, PPortalVec & vPortals);
	~Lighting();

	void RenderAllLights(std::vector<std::shared_ptr<Object>> vObjects);
	void RenderLights(std::shared_ptr<Object> Object);
	void RenderDepthMap();

	size_t getLightsCount() { return m_Lights.size(); };
	size_t getPointLightsCount();
	size_t getDirLightsCount();

private:
	std::vector<std::shared_ptr<Light>> & m_Lights;
	PPortalVec & m_Portals;
	//std::shared_ptr<Shader> shadowShader = AquireShader("");
};
typedef std::vector<std::shared_ptr<Light>> PLightVec;
