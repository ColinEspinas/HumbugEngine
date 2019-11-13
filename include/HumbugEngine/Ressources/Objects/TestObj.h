#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Components/MeshRenderer.h"

class TestObj : public Object
{
public:
	TestObj(std::string obj, float _scale = 1.0f, std::string _texture = "White.bmp")
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh(obj.c_str()));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture(_texture.c_str());
		AddComponent(MR);
		m_scale = Vector3(_scale);
	}
	virtual ~TestObj() {}
};