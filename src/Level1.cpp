#include "HumbugEngine/Level1.h"
#include "HumbugEngine/Tunnel.h"
#include "HumbugEngine/Ground.h"

void Level1::Load(Player& player)
{
	AddObject(player.getTorch());

	AddObject(std::make_shared<LightObject>(false));
	ObjectCast::Cast<LightObject>(GetObject(GetObjectAmount() - 1))
		->AddComponent<PointLight>(Vector3(0.0f, 1.0f, 0.0f), 1.0f, 0.09f, 0.032f, Vector3(1.0f, 0.9f, 0.8f), Vector3(1.0f, 0.9f, 0.8f));

	//lights.push_back(std::shared_ptr<PointLight>(new PointLight(Vector3(0.0f, 200.0f, 0.0f), 1.0f, 0.014f, 0.0007f, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.8f, 0.6f))));
	//lights.push_back(std::shared_ptr<PointLight>(new PointLight(Vector3(0.0f, 1.0f, 0.0f), 1.0f, 0.09f, 0.032f, Vector3(1.0f, 0.9f, 0.8f), Vector3(1.0f, 0.9f, 0.8f))));
	//lights.push_back(std::shared_ptr<DirLight>(new DirLight(Vector3(0.2f, 0.0f, 0.2f))));
	//lights.push_back(std::shared_ptr<PointLight>(new PointLight(Vector3(-6.80f, 1.0f, -5.48f), 1.0f, 0.09f, 0.032f, Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 0.0f, 1.0f))));

	std::shared_ptr<Tunnel> tunnel1(std::make_shared<Tunnel>(Tunnel::NORMAL));
	tunnel1->m_pos = Vector3(-2.4f, 0, -1.8f);
	tunnel1->m_scale = Vector3(1, 1, 4.8f);
	AddObject(tunnel1);

	std::shared_ptr<Tunnel> tunnel2(std::make_shared<Tunnel>(Tunnel::NORMAL));
	tunnel2->m_pos = Vector3(2.4f, 0, 0);
	tunnel2->m_scale = Vector3(1, 1, 0.6f);
	AddObject(tunnel2);

	std::shared_ptr<Ground> ground(std::make_shared<Ground>());
	ground->m_scale *= 1.2f;
	AddObject(ground);

	std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
	tunnel1->SetDoor1(*portal1);
	AddObject(portal1);

	std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
	tunnel2->SetDoor1(*portal2);
	AddObject(portal2);

	std::shared_ptr<Portal> portal3(std::make_shared<Portal>());
	tunnel1->SetDoor2(*portal3);
	AddObject(portal3);

	std::shared_ptr<Portal> portal4(std::make_shared<Portal>());
	tunnel2->SetDoor2(*portal4);
	AddObject(portal4);

	Portal::Connect(portal1, portal2);
	Portal::Connect(portal3, portal4);

	player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT, 5));
}
