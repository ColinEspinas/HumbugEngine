#pragma once
#include "..\..\..\Object.h"
#include "..\..\..\Resources.h"

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
		mesh = AquireMesh("MazeRoom/Maze000.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
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
		mesh = AquireMesh("MazeRoom/Maze001.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
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
		mesh = AquireMesh("MazeRoom/Maze002.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
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
		mesh = AquireMesh("MazeRoom/Maze003.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
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
		mesh = AquireMesh("MazeRoom/Maze004.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
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
		mesh = AquireMesh("MazeRoom/Maze005.obj");
		shader = AquireShader("texture");
		texture = AquireTexture("Bush.bmp");
		scale = Vector3(2.5f);
		euler += Vector3(3 * GH_PI / 2, 0, 0);
	}
	virtual ~MazeRoom_5() {}
	int ID() const override { return 15; }
};