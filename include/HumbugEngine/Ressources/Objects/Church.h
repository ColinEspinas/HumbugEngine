#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Components/MeshRenderer.h"

class Church : public Object
{
public:
	Church()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("Church.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("white.bmp");
		AddComponent(MR);
		m_scale = Vector3(1e-2f);
	}
	virtual ~Church() {}
};