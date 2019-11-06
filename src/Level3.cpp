#include "HumbugEngine/Level3.h"
#include "HumbugEngine/Pillar.h"
#include "HumbugEngine/Ground.h"
#include "HumbugEngine/Statue.h"
#include "HumbugEngine/PillarRoom.h"

void Level3::Load(Player& player) {
	lights.push_back(player.getTorch());

  //Room 1
  std::shared_ptr<Pillar> pillar1(new Pillar);
  AddObject(pillar1);

  std::shared_ptr<PillarRoom> pillarRoom1(new PillarRoom);
  AddObject(pillarRoom1);

  std::shared_ptr<Ground> ground1(new Ground);
  ground1->m_scale *= 2.0f;
  AddObject(ground1);

  std::shared_ptr<Statue> statue1(new Statue("teapot.obj"));
  statue1->m_pos = Vector3(0, 0.5f, 9);
  statue1->m_scale = Vector3(0.5f);
  statue1->m_euler.y = GH_PI / 2;
  AddObject(statue1);

  //Room 2
  std::shared_ptr<Pillar> pillar2(new Pillar);
  pillar2->m_pos = Vector3(200, 0, 0);
  AddObject(pillar2);

  std::shared_ptr<PillarRoom> pillarRoom2(new PillarRoom);
  pillarRoom2->m_pos = Vector3(200, 0, 0);
  AddObject(pillarRoom2);

  std::shared_ptr<Ground> ground2(new Ground);
  ground2->m_pos = Vector3(200, 0, 0);
  ground2->m_scale *= 2.0f;
  AddObject(ground2);

  std::shared_ptr<Statue> statue2(new Statue("bunny.obj"));
  statue2->m_pos = Vector3(200, -0.4f, 9);
  statue2->m_scale = Vector3(14.0f);
  statue2->m_euler.y = GH_PI;
  AddObject(statue2);

  //Room 3
  std::shared_ptr<Pillar> pillar3(new Pillar);
  pillar3->m_pos = Vector3(400, 0, 0);
  AddObject(pillar3);

  std::shared_ptr<PillarRoom> pillarRoom3(new PillarRoom);
  pillarRoom3->m_pos = Vector3(400, 0, 0);
  AddObject(pillarRoom3);

  std::shared_ptr<Ground> ground3(new Ground);
  ground3->m_pos = Vector3(400, 0, 0);
  ground3->m_scale *= 2.0f;
  AddObject(ground3);

  std::shared_ptr<Statue> statue3(new Statue("suzanne.obj"));
  statue3->m_pos = Vector3(400, 0.9f, 9);
  statue3->m_scale = Vector3(1.2f);
  statue3->m_euler.y = GH_PI;
  AddObject(statue3);

  //Portals
  std::shared_ptr<Portal> portal1(new Portal);
  pillarRoom1->SetPortal(*portal1);
  AddObject(portal1);

  std::shared_ptr<Portal> portal2(new Portal);
  pillarRoom2->SetPortal(*portal2);
  AddObject(portal2);

  std::shared_ptr<Portal> portal3(new Portal);
  pillarRoom3->SetPortal(*portal3);
  AddObject(portal3);

  Portal::Connect(portal1->front, portal2->back);
  Portal::Connect(portal2->front, portal3->back);
  Portal::Connect(portal3->front, portal1->back);

  player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT, 3));
}
