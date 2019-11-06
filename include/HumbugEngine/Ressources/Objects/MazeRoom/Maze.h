#pragma once
#include "HumbugEngine/Ressources/Objects/MazeRoom/MazeRoom.h"
#include "HumbugEngine/Objects/Portal.h"
#include <array>
#include <time.h>

class MazeCase
{
public:
	MazeCase(int id = 0, int section = 0, int X = 0, int Y = 0);
	std::shared_ptr<MazeRoom> get() const;
	void set(int id, int R);
	void _set(std::array<bool, 4> composition);
	void Rotate(int R);
	void Translate(Vector3 T);

	int Section = 0;
	int X = 0, Y = 0;

	std::array<bool, 4> NESW() const { return DecypherID(); }
	bool Up() const { return DecypherID()[0]; }
	bool Right() const { return DecypherID()[1]; }
	bool Down() const { return DecypherID()[2]; }
	bool Left() const { return DecypherID()[3]; }

	void DebugPrint(int Id);

private:
	std::shared_ptr<MazeRoom> m_room;
	Vector3 m_pos;
	int m_Ry;

	std::array<bool, 4> DecypherID() const;
};
typedef std::vector<std::shared_ptr<MazeCase>> PMazeVec;


class MazePortal
{
public:
	enum DIRECTION
	{
		TOP = 0,
		LEFT = 1,
		BOTTOM = 2,
		RIGHT = 3
	};
	enum TYPE
	{
		VERTICAL = 0,
		HORIZONTAL = 1
	};

public:
	MazePortal(std::shared_ptr<MazeCase> ref, DIRECTION dir, int sectionWidth);
	std::shared_ptr<Portal> get() const { return m_Content; }
	int GetSection() const { return m_Parent->Section; }

private:
	std::shared_ptr<MazeCase> m_Parent;
	std::shared_ptr<Portal> m_Content;
	TYPE m_Direction;

	Vector3 m_LocalOffset;
};
typedef std::vector<std::shared_ptr<MazePortal>> PMazePortalVec;


class Maze
{
public:
	Maze(const unsigned int seed = time(NULL), int nSection = 4, int width = 4, int height = 4, int nJonction = 2);
	void Apply(PObjectVec& Objects, PPortalVec& Portals);

	const int amountOfSection, SectionWidth, SectionHeight;

private:
	PMazeVec m_Rooms;
	PPortalVec m_Portals;

	bool Contain(std::vector<int> ref, int value);
	std::vector<int> NeighbourIndexes(PMazeVec Content, std::shared_ptr<MazeCase> Instance, bool checkIfOpened = true);
};