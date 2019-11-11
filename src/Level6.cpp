#include "HumbugEngine/Level6.h"
#include "HumbugEngine/Floorplan.h"
#include "HumbugEngine/Objects/LightObject.h"

void Level6::Load(Player& player) {

	AddObject(player.getTorch());
	AddObject(std::make_shared<LightObject>(false));
	ObjectCast::Cast<LightObject>(GetObject(GetObjectAmount() - 1))
		->AddComponent<PointLight>(Vector3(0.0f, 2.0f, 0.0f), 1.0f, 0.09f, 0.032f, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.8f, 0.8f));

	std::shared_ptr<Floorplan> floorplan(std::make_shared<Floorplan>());
	AddObject(floorplan);
	floorplan->AddPortals(m_Objects);

	player.SetPosition(Vector3(2, GH_PLAYER_HEIGHT, 2));
}
