#include "HumbugEngine/Level2.h"
#include "HumbugEngine/House.h"

void Level2::Load(Player& player) {
	lights.push_back(player.getTorch());

  std::shared_ptr<House> house1(std::make_shared<House>("three_room.bmp"));
  house1->m_pos = Vector3(0, 0, -20);
  AddObject(house1);

  std::shared_ptr<House> house2;
  if (num_rooms > 4) {
	  house2 = std::make_shared<House>("three_room2.bmp");
    house2->m_pos = Vector3(200, 0, -20);
    AddObject(house2);
  }

  if (num_rooms == 1) {
    std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
    house1->SetDoor1(*portal1);
    AddObject(portal1);

    std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
    house1->SetDoor4(*portal2);
    AddObject(portal2);

    Portal::Connect(portal1, portal2);
  } else if (num_rooms == 2) {
    std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
    house1->SetDoor2(*portal1);
    AddObject(portal1);

    std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
    house1->SetDoor4(*portal2);
    AddObject(portal2);

    Portal::Connect(portal1, portal2);
  } else if (num_rooms == 3) {
    std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
    house1->SetDoor3(*portal1);
    AddObject(portal1);

    std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
    house1->SetDoor4(*portal2);
    AddObject(portal2);

    Portal::Connect(portal1, portal2);
  } else if (num_rooms == 4) {
  } else if (num_rooms == 5) {
    std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
    house1->SetDoor4(*portal1);
    AddObject(portal1);

    std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
    house2->SetDoor2(*portal2);
    AddObject(portal2);

    std::shared_ptr<Portal> portal3(std::make_shared<Portal>());
    house2->SetDoor1(*portal3);
    AddObject(portal3);

    Portal::Connect(portal1->front, portal2->back);
    Portal::Connect(portal2->front, portal3->back);
    Portal::Connect(portal3->front, portal1->back);
  } else if (num_rooms == 6) {
    std::shared_ptr<Portal> portal1(std::make_shared<Portal>());
    house1->SetDoor4(*portal1);
    AddObject(portal1);

    std::shared_ptr<Portal> portal2(std::make_shared<Portal>());
    house2->SetDoor3(*portal2);
    AddObject(portal2);

    std::shared_ptr<Portal> portal3(std::make_shared<Portal>());
    house2->SetDoor1(*portal3);
    AddObject(portal3);

    Portal::Connect(portal1->front, portal2->back);
    Portal::Connect(portal2->front, portal3->back);
    Portal::Connect(portal3->front, portal1->back);
  }

  player.SetPosition(Vector3(3, GH_PLAYER_HEIGHT, 3));
}
