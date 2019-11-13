#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Components/MeshRenderer.h"

// Maze Room Interface
class MazeRoom : public Object
{
public:
	virtual int ID() const = 0;
};

// Maze Room 0
class MazeRoom_0 : public MazeRoom
{
public:
	MazeRoom_0()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze000.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_0() {}
	int ID() const override { return 0; }
};

// Maze Room 1
class MazeRoom_1 : public MazeRoom
{
public:
	MazeRoom_1()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze001.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_1() {}
	int ID() const override { return 8; }
};

// Maze Room 2
class MazeRoom_2 : public MazeRoom
{
public:
	MazeRoom_2()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze002.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_2() {}
	int ID() const override { return 3; }
};

// Maze Room 3
class MazeRoom_3 : public MazeRoom
{
public:
	MazeRoom_3()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze003.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_3() {}
	int ID() const override { return 10; }
};

// Maze Room 4
class MazeRoom_4 : public MazeRoom
{
public:
	MazeRoom_4()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze004.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_4() {}
	int ID() const override { return 11; }
};

// Maze Room 5
class MazeRoom_5 : public MazeRoom
{
public:
	MazeRoom_5()
	{
		std::shared_ptr<MeshRenderer> MR = std::make_shared<MeshRenderer>();
		MR->AddMesh(AquireMesh("MazeRoom/Maze005.obj"));
		MR->GetMesh(0)->shader = AquireShader("texture");
		MR->GetMesh(0)->texture = AquireTexture("Bush.bmp");
		AddComponent(MR);
		m_scale = Vector3(2.5f);
		m_euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_5() {}
	int ID() const override { return 15; }
};