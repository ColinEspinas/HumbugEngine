#include "HumbugEngine/Level6.h"
#include "HumbugEngine/Floorplan.h"

void Level6::Load(Player& player) {

	lights.push_back(player.getTorch());
	lights.push_back(std::shared_ptr<PointLight>(new PointLight(Vector3(0.0f, 2.0f, 0.0f), 1.0f, 0.09f, 0.032f, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.8f, 0.8f))));

	std::shared_ptr<Floorplan> floorplan(std::make_shared<Floorplan>());
	AddObject(floorplan);
	floorplan->AddPortals(portals);

	player.SetPosition(Vector3(2, GH_PLAYER_HEIGHT, 2));
}
