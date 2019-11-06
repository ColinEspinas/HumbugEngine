#include "HumbugEngine/Level4.h"
#include "HumbugEngine/Tunnel.h"
#include "HumbugEngine/Ground.h"

void Level4::Load(Player& player) {
	lights.push_back(player.getTorch());

  std::shared_ptr<Tunnel> tunnel1(new Tunnel(Tunnel::SLOPE));
  tunnel1->m_pos = Vector3(0, 0, 0);
  tunnel1->m_scale = Vector3(1, 1, 5);
  tunnel1->m_euler.y = GH_PI;
  AddObject(tunnel1);

  std::shared_ptr<Ground> ground1(new Ground(true));
  ground1->m_scale *= Vector3(1, 2, 1);
  AddObject(ground1);

  std::shared_ptr<Tunnel> tunnel2(new Tunnel(Tunnel::SLOPE));
  tunnel2->m_pos = Vector3(200, 0, 0);
  tunnel2->m_scale = Vector3(1, 1, 5);
  AddObject(tunnel2);

  std::shared_ptr<Ground> ground2(new Ground(true));
  ground2->m_pos = Vector3(200, 0, 0);
  ground2->m_scale *= Vector3(1, 2, 1);
  ground2->m_euler.y = GH_PI;
  AddObject(ground2);

  std::shared_ptr<Portal> portal1(new Portal());
  tunnel1->SetDoor1(*portal1);
  AddObject(portal1);

  std::shared_ptr<Portal> portal2(new Portal());
  tunnel1->SetDoor2(*portal2);
  AddObject(portal2);

  std::shared_ptr<Portal> portal3(new Portal());
  tunnel2->SetDoor1(*portal3);
  portal3->m_euler.y -= GH_PI;
  AddObject(portal3);

  std::shared_ptr<Portal> portal4(new Portal());
  tunnel2->SetDoor2(*portal4);
  portal4->m_euler.y -= GH_PI;
  AddObject(portal4);

  Portal::Connect(portal1, portal4);
  Portal::Connect(portal2, portal3);

  player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT - 2, 8));
}
