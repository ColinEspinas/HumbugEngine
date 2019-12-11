#include "HumbugEngine/Ressources/Levels/Level_1.h"
#include "HumbugEngine/Ground.h"
#include "HumbugEngine/Ressources/Objects/TestObj.h"
#include "HumbugEngine/Ressources/Objects/MazeRoom/Maze.h"

#include "HumbugEngine/Animator.h"

void Level_1::Load(PObjectVec & objs, PLightVec& lights, PPortalVec & portals, PQuadVec& quads, Player & player)
{
	lights.push_back(player.getTorch());

	//Maze M(3);
	//M.Apply(objs, portals);


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
	

	//*//
	std::shared_ptr<TestObj> testOBJ(new TestObj("Church.obj", 15e-3f));

	// Animations
	testOBJ->animator->Build({
		{ {1,1}, { {2,0},		{6,3.14f},		{10,0} } },
		{ {0,1}, { {2,0},		{5,-2},			{8,0} } },
		{ {2,1}, { {2,15e-3f},	{6,30e-3f},		{10,15e-3f} } }
	});

	//testOBJ->pos += Vector3(5.0f, 0, 0);
	objs.push_back(testOBJ);

	std::shared_ptr<Ground> ground(std::make_shared<Ground>());
	ground->scale *= 1.2f;
	objs.push_back(ground);


	std::shared_ptr<UIQuad> _quad(new UIQuad("Bush.bmp"));
	quads.push_back(_quad);
	//*/

	player.SetPosition(Vector3(0, GH_PLAYER_HEIGHT, 0));
}
