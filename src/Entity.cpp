#include "HumbugEngine/Physics/Entity.h"

Entity::Entity(std::shared_ptr<Object>& obj, std::shared_ptr<PhysicRuleset>& pR)
	: physics(pR)
{
	Reset();
	if (obj->Contain<MeshRenderer>())
	{
		this->RemoveComponent<MeshRenderer>();
		AddComponent(obj->GetComponent<MeshRenderer>());
	}
	physics->SetBody(this);
}

void Entity::Reset()
{
	Physical::Reset();
	physics->PerReset();
}

void Entity::Update()
{
	Physical::Update();
	physics->PerFrame();
}

void Entity::OnCollide(Object & other, const Vector3 & push)
{
	auto newPush = physics->PerHit(other, push);
	Physical::OnCollide(other, newPush);
}
