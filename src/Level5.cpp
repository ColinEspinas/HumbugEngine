#include "HumbugEngine/Level5.h"
#include "HumbugEngine/Tunnel.h"
#include "HumbugEngine/Ground.h"

void Level5::Load(Player& player) {
	lights.push_back(player.getTorch());

  std::shared_ptr<Tunnel> tunnel1(new Tunnel(Tunnel::SCALE));
  tunnel1->m_pos = Vector3(-1.2f, 0, 0);
  tunnel1->m_scale = Vector3(1, 1, 2.4f);
  AddObject(tunnel1);

  std::shared_ptr<Ground> ground1(new Ground());
  ground1->m_scale *= 1.2f;
  AddObject(ground1);

  std::shared_ptr<Tunnel> tunnel2(new Tunnel(Tunnel::NORMAL));
  tunnel2->m_pos = Vector3(201.2f, 0, 0);
  tunnel2->m_scale = Vector3(1, 1, 2.4f);
  AddObject(tunnel2);

  std::shared_ptr<Ground> ground2(new Ground());
  ground2->m_pos = Vector3(200, 0, 0);
  ground2->m_scale *= 1.2f;
  AddObject(ground2);

  std::shared_ptr<Portal> portal1(new Portal());
  tunnel1->SetDoor1(*portal1);
  AddObject(portal1);

  std::shared_ptr<Portal> portal2(new Portal());
  tunnel2->SetDoor1(*portal2);
  AddObject(portal2);

  std::shared_ptr<Portal> portal3(new Portal());
  tunnel1->SetDoor2(*portal3);
  AddObject(portal3);

  std::shared_ptr<Portal> portal4(new Portal());
  tunnel2->SetDoor2(*portal4);
  AddObject(portal4);

  Portal::Connect(portal1, portal2);
  Portal::Connect(portal3, portal4);

  std::shared_ptr<Tunnel> tunnel3(new Tunnel(Tunnel::NORMAL));
  tunnel3->m_pos = Vector3(-1, 0, -4.2f);
  tunnel3->m_scale = Vector3(0.25f, 0.25f, 0.6f);
  tunnel3->m_euler.y = GH_PI/2;
  AddObject(tunnel3);

  player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT, 5));
}
