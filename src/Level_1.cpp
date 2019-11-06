#include "HumbugEngine/Ressources/Levels/Level_1.h"
#include "HumbugEngine/Ground.h"
#include "HumbugEngine\Ressources\Objects\TestObj.h"
#include "HumbugEngine\Ressources\Objects\MazeRoom\Maze.h"

void Level_1::Load(Player & player)
{
	lights.push_back(player.getTorch());

	Maze M(3);
	M.Apply();


	/*//
	std::shared_ptr<Ground> ground(std::make_shared<Ground>());
	ground->scale *= 1.2f;
	objs.push_back(ground);

	MazeCase Case(5);
	objs.push_back(Case.get());

	PPortalVec PPV;
	for (int ii = 0; ii < 4; ii++)
	{
		PPV.push_back(std::make_shared<Portal>());
		Case.SetPortal(PPV[ii], ii);
		portals.push_back(PPV[ii]);
	}
	//*/

	
	/*//
	std::shared_ptr<MazeRoom_1> M1(std::make_shared<MazeRoom_1>());
	M1->pos += Vector3(0, 0, 5.0f);
	M1->euler += Vector3(0, -GH_PI / 2, 0);
	objs.push_back(M1);

	std::shared_ptr<MazeRoom_2> M2(std::make_shared<MazeRoom_2>());
	M2->pos += Vector3(5.0f, 0, 5.0f);
	M2->euler += Vector3(0, -GH_PI / 2, 0);
	objs.push_back(M2);

	std::shared_ptr<MazeRoom_3> M3(std::make_shared<MazeRoom_3>());
	M3->pos += Vector3(5.0f, 0, 0);
	objs.push_back(M3);

	std::shared_ptr<MazeRoom_4> M4(std::make_shared<MazeRoom_4>());
	M4->pos += Vector3(5.0f, 0, -5.0f);
	objs.push_back(M4);

	std::shared_ptr<MazeRoom_5> M5(std::make_shared<MazeRoom_5>());
	M5->pos += Vector3(0, 0, -5.0f);
	objs.push_back(M5);
	//*/
	

	/*//
	std::shared_ptr<TestObj> MazeRoom1(new TestObj("MazeRoom/Maze001.obj", 2.5f));
	MazeRoom1->pos += Vector3(5.0f, 0, 0);
	objs.push_back(MazeRoom1);
	//*/

	player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT, 0));
}
