#include "HumbugEngine/Ressources/Objects/MazeRoom/Maze.h"
#include "HumbugEngine/Ground.h"

#include <iostream>

#define F_DIR_X(D) -pow(D, 3)/3.0f + pow(D, 2)*2.0f - D*8.0f/3.0f
#define F_DIR_Y(D) pow(D, 3)/3.0f - pow(D, 2) - D/3.0f + 1.0f


// MazeCase: Create Maze
MazeCase::MazeCase(int Index, int section, int x, int y)
	: Section(section), X(x), Y(y), m_room(std::make_shared<MazeRoom_0>())
{
	this->set(Index, 0);
	m_pos = m_room->m_pos;
}


// MazeCase: Return Room
std::shared_ptr<MazeRoom> MazeCase::get() const
{
	m_room->m_euler.y = float(m_Ry) * GH_PI / 2;
	m_room->m_pos = m_pos;
	return m_room;
}


// MazeCase: Reset MazeRoom relative Data
void MazeCase::set(int id, int R)
{
	switch (id)
	{
	case 1: m_room = std::make_shared<MazeRoom_1>(); break;
	case 2: m_room = std::make_shared<MazeRoom_2>(); break;
	case 3: m_room = std::make_shared<MazeRoom_3>(); break;
	case 4: m_room = std::make_shared<MazeRoom_4>(); break;
	case 5: m_room = std::make_shared<MazeRoom_5>(); break;
	default: m_room = std::make_shared<MazeRoom_0>(); break;
	}
	m_Ry = 0;
	this->Rotate(R);
}


// MazeCase: Set MazeRoom Properties to Match Composition
void MazeCase::_set(std::array<bool, 4> composition)
{
	std::vector<std::array<int, 2>> Possibilities;
	for (int ii = 0; ii < 5; ii++)
		for (int jj = 0; jj < 4; jj++)
			Possibilities.push_back({ ii + 1, jj });
	MazeCase Instance;
	for (auto P : Possibilities)
	{
		Instance.set(P[0], P[1]);
		if (Instance.NESW() == composition)
		{
			this->set(P[0], P[1]);
			break;
		}
	}
}


// MazeCase: Rotate Room
void MazeCase::Rotate(int R)
{
	m_Ry += R < 0 ? -(-R % 4) : R % 4;
}


// MazeCase: Translate Room
void MazeCase::Translate(Vector3 T)
{
	m_pos += T;
}


// MazeCase: Print Debug Information
void MazeCase::DebugPrint(int Id)
{
#ifdef _DEBUG
	std::cout << std::endl << Id << " " << m_Ry << ": ";
#endif
}


// MazeCase: Decypher Room ID
std::array<bool, 4> MazeCase::DecypherID() const
{
	int tVal = m_room->ID();
	std::array<bool, 4> temp, res;
	for (int ii = 3; ii >= 0; ii--)
	{
		temp[3 - ii] = tVal >= pow(2, ii);
		if (temp[3 - ii])
			tVal -= (int)pow(2, ii);
	}
	for (int jj = 0; jj < 4; jj++)
		res[jj] = temp[(jj + m_Ry) % 4];

	return res;
}


// ---------- ---------- ---------- ---------- ---------- //


// Maze: Constructor
Maze::Maze(const unsigned int seed, int nS, int W, int H, int nJ)
	: amountOfSection(nS < 2 ? 2 : nS)
	, SectionWidth(W < 2 ? 2 : W)
	, SectionHeight(H < 2 ? 2 : H)
{
	// Pre-Generation
	std::srand(seed);
	std::vector<std::vector<PMazeVec>> Board;
	for (int S = 0; S < amountOfSection; S++)
	{
		Board.push_back({});
		for (int Y = 0; Y < SectionHeight; Y++)
		{
			Board[S].push_back({});
			for (int X = 0; X < SectionWidth; X++)
				Board[S][Y].push_back(std::make_shared<MazeCase>(((int)std::rand() % 5) + 1, S, X, Y));
		}
	}

	// Possibilities Construction
	std::vector<std::array<int, 2>> Possibilities;
	std::vector<std::array<int, 2>> PosInstance;
	for (int ii = 0; ii < 5; ii++)
	{
		switch (ii + 1)
		{
		case 3:
			for (int jj = 0; jj < 2; jj++)
				Possibilities.push_back({ ii + 1, jj * 2 });
			break;
		case 5:
			Possibilities.push_back({ ii + 1, 0 });
			break;
		default:
			for (int jj = 0; jj < 4; jj++)
				Possibilities.push_back({ ii + 1, jj });
			break;
		}
	}

	// Ensure Validity of Each Cases in Maze
	std::shared_ptr<MazeCase> RoomInstance;
	std::array<int, 2> IndexesInstance;
	int tIndex;
	for (int S = 0; S < amountOfSection; S++)
		for (int Y = 0; Y < SectionHeight; Y++)
			for (int X = 0; X < SectionWidth; X++)
			{
				PosInstance = Possibilities;
				RoomInstance = Board[S][Y][X];
				while (true)
				{
					if (PosInstance.empty())
					{
						RoomInstance->set(0, 0);
						break;
					}
					tIndex = std::rand() % PosInstance.size();
					IndexesInstance = PosInstance[tIndex];
					PosInstance.erase(PosInstance.begin() + tIndex);

					if ((X == 0 && RoomInstance->Left())
						|| (Y == 0 && RoomInstance->Up())
						|| (X == SectionWidth - 1 && RoomInstance->Right())
						|| (Y == SectionHeight - 1 && RoomInstance->Down()))
					{
						RoomInstance->set(IndexesInstance[0], IndexesInstance[1]);
						continue;
					}

					if (X != 0)
						if (Board[S][Y][X - 1]->Right() != RoomInstance->Left())
						{
							RoomInstance->set(IndexesInstance[0], IndexesInstance[1]);
							continue;
						}
					if (Y != 0)
						if (Board[S][Y - 1][X]->Down() != RoomInstance->Up())
						{
							RoomInstance->set(IndexesInstance[0], IndexesInstance[1]);
							continue;
						}
					break;
				}
			}

	// Find and Count the Amount of Paths after Correction
	// Then, Join Each Path as One
	PMazeVec MazeInstance, CaseTreeInstance;
	int tSize;
	std::vector<PMazeVec> AllPaths;
	std::vector<std::array<std::pair<std::shared_ptr<MazeCase>, int>, 2>> AllNeighbors;
	for (int S = 0; S < amountOfSection; S++)
	{
		AllPaths.clear();
		MazeInstance.clear();
		for (int Y = 0; Y < SectionHeight; Y++)
			for (int X = 0; X < SectionWidth; X++)
				if (Board[S][Y][X])
					if (Board[S][Y][X]->get())
						MazeInstance.push_back(Board[S][Y][X]);

		// Loop while MazeInstance is not Empty
		while (!MazeInstance.empty())
		{
			AllPaths.push_back({});
			CaseTreeInstance.clear();
			CaseTreeInstance.push_back(MazeInstance[0]);
			MazeInstance.erase(MazeInstance.begin());

			// Loop while Path Finding is Viable
			while (!CaseTreeInstance.empty())
			{
				tSize = CaseTreeInstance.size();

				// Read Each MazeCase in Tree
				for (unsigned int ii = 0; ii < CaseTreeInstance.size(); ii++)
				{

					// Look for MazeCase Next to Instance in Specified Direction
					for (unsigned int Index = 0; Index < MazeInstance.size(); Index)
					{
						// Top
						if ((CaseTreeInstance[ii]->X == MazeInstance[Index]->X
							&& CaseTreeInstance[ii]->Y == MazeInstance[Index]->Y + 1
							&& CaseTreeInstance[ii]->Up()) ||
						// Right
							(CaseTreeInstance[ii]->X == MazeInstance[Index]->X - 1
							&& CaseTreeInstance[ii]->Y == MazeInstance[Index]->Y
							&& CaseTreeInstance[ii]->Right()) ||
						// Bottom
							(CaseTreeInstance[ii]->X == MazeInstance[Index]->X
							&& CaseTreeInstance[ii]->Y == MazeInstance[Index]->Y - 1
							&& CaseTreeInstance[ii]->Down()) ||
						// Left
							(CaseTreeInstance[ii]->X == MazeInstance[Index]->X + 1
							&& CaseTreeInstance[ii]->Y == MazeInstance[Index]->Y
							&& CaseTreeInstance[ii]->Left()))
						{
							CaseTreeInstance.push_back(MazeInstance[Index]);
							MazeInstance.erase(MazeInstance.begin() + Index);
						}
						else Index++;
					}
				}
				if (tSize != 0)
					for (int Range = 0; Range < tSize; Range++)
					{
						AllPaths.rbegin()->push_back(CaseTreeInstance[0]);
						CaseTreeInstance.erase(CaseTreeInstance.begin());
					}
			}
		}

		// Determine if two Cases from Different Paths are Close to Each other
		const int amountOfPath = AllPaths.size();
		if (amountOfPath > 1)
		{
			for (int ii = 0; ii < amountOfPath - 1; ii++)
				for (int jj = ii + 1; jj < amountOfPath; jj++)
					for (auto C1 : AllPaths[ii])
						for (auto C2 : AllPaths[jj])
							if (pow(float(C1->X - C2->X + C1->Y - C2->Y), 2) == 1.0f)
								AllNeighbors.push_back({ std::pair<std::shared_ptr<MazeCase>, int>{C1,ii}, {C2,jj} });
		}

		// Shuffle Vector of Neighbors Randomly
		auto RandomNeighbors = AllNeighbors;
		int tIndex;
		if (amountOfPath > 1)
		{
			RandomNeighbors.clear();
			while (!AllNeighbors.empty())
			{
				tIndex = std::rand() % AllNeighbors.size();
				RandomNeighbors.push_back(AllNeighbors[tIndex]);
				AllNeighbors.erase(AllNeighbors.begin() + tIndex);
			}
		}

		// Chose Pair of Cases to Join Paths
		std::vector<std::vector<int>> AllPathIndexes;
		std::vector<int> V1, V2;
		bool hasBeenJoining;
		if (amountOfPath > 1)
		{
			for (int a = 0; a < amountOfPath; a++)
				AllPathIndexes.push_back({ a });

			for (unsigned int ii = 0; ii < AllPathIndexes.size() - 1; ii++)
				for (unsigned int jj = ii + 1; jj < AllPathIndexes.size(); jj)
				{
					V1 = AllPathIndexes[ii];
					V2 = AllPathIndexes[jj];

					if (V1 != V2)
					{
						hasBeenJoining = false;

						for (auto N : RandomNeighbors)
							if ((Contain(V1, N[0].second) && Contain(V2, N[1].second))
								|| (Contain(V1, N[1].second) && Contain(V2, N[0].second)))
							{
								auto Boussole1 = N[0].first->NESW(), Boussole2 = N[1].first->NESW();

								// Top
								if (N[0].first->X == N[1].first->X
									&& N[0].first->Y == N[1].first->Y + 1)
								{
									hasBeenJoining = true;
									Boussole1[0] = true;
									Boussole2[2] = true;
									N[0].first->_set(Boussole1);
									N[1].first->_set(Boussole2);
									break;
								}
								// Right
								else if (N[0].first->X == N[1].first->X - 1
									&& N[0].first->Y == N[1].first->Y)
								{
									hasBeenJoining = true;
									Boussole1[1] = true;
									Boussole2[3] = true;
									N[0].first->_set(Boussole1);
									N[1].first->_set(Boussole2);
									break;
								}
								// Bottom
								else if (N[0].first->X == N[1].first->X
									&& N[0].first->Y == N[1].first->Y - 1)
								{
									hasBeenJoining = true;
									Boussole1[2] = true;
									Boussole2[0] = true;
									N[0].first->_set(Boussole1);
									N[1].first->_set(Boussole2);
									break;
								}
								// Left
								else if (N[0].first->X == N[1].first->X + 1
									&& N[0].first->Y == N[1].first->Y)
								{
									hasBeenJoining = true;
									Boussole1[3] = true;
									Boussole2[1] = true;
									N[0].first->_set(Boussole1);
									N[1].first->_set(Boussole2);
									break;
								}
							}
						if (hasBeenJoining)
						{
							for (unsigned int b = 0; b < AllPathIndexes[jj].size(); b++)
								AllPathIndexes[jj - 1].push_back(AllPathIndexes[jj][b]);
							AllPathIndexes.erase(AllPathIndexes.begin() + jj);
						}
						else jj++;
					}
				}
		}
	}

	// Rough Empty Cases Correction
	PMazeVec tAllCases;
	std::array<bool, 4> CorrectionFiller;
	for (int S = 0; S < amountOfSection; S++)
	{
		tAllCases.clear();
		for (auto vC : Board[S])
			for (auto C : vC)
				tAllCases.push_back(C);
		for (unsigned int ii = 0; ii < tAllCases.size(); ii++)
		{
			if (tAllCases[ii]->get()->ID() == 0)
			{
				for (int a = 0; a < 4; a++)
					CorrectionFiller[a] = false;
				for (int jj : NeighbourIndexes(tAllCases, tAllCases[ii], false))
				{
					// Top
					if (tAllCases[ii]->X == tAllCases[jj]->X
						&& tAllCases[ii]->Y == tAllCases[jj]->Y + 1
						&& tAllCases[jj]->Down())
					{
						CorrectionFiller[0] = true;
					}
					// Right
					else if (tAllCases[ii]->X == tAllCases[jj]->X - 1
						&& tAllCases[ii]->Y == tAllCases[jj]->Y
						&& tAllCases[jj]->Left())
					{
						CorrectionFiller[1] = true;
					}
					// Bottom
					else if (tAllCases[ii]->X == tAllCases[jj]->X
						&& tAllCases[ii]->Y == tAllCases[jj]->Y - 1
						&& tAllCases[jj]->Up())
					{
						CorrectionFiller[2] = true;
					}
					// Left
					else if (tAllCases[ii]->X == tAllCases[jj]->X + 1
						&& tAllCases[ii]->Y == tAllCases[jj]->Y
						&& tAllCases[jj]->Right())
					{
						CorrectionFiller[3] = true;
					}
				}
				tAllCases[ii]->_set(CorrectionFiller);
			}
		}
	}
	/// TODO

	//*//
	// Create Portal Jonction between Sections
	int nJonction = GH_MIN<int>(GH_MIN<int>(SectionHeight, SectionWidth) - 1, (nJ < nS ? (nJ < 2 ? (nS == 2 ? 1 : 2) : nJ) : nS - 1));
	std::cout << "Amount of Jonction: " << nJonction << std::endl; //DEBUG

	std::vector<std::array<int, 2>> ExistingJonctionPos;
	PMazePortalVec MazePortalCases;
	std::shared_ptr<MazeCase> tCaseInstance;
	int tACIndex, tEraseCount;
	std::vector<int> tEraseIndexes;
	for (int S = 0; S < amountOfSection; S++)
	{
		tAllCases.clear();
		for (auto vC : Board[S])
			for (auto C : vC)
				tAllCases.push_back(C);
		for (int ii = 0; ii < nJonction; ii)
		{
			std::cout << "Section: " << S << " | Remaining Cases: " << tAllCases.size() << std::endl; //DEBUG
			tACIndex = std::rand() % tAllCases.size();
			tCaseInstance = tAllCases[tACIndex];
			tAllCases.erase(tAllCases.begin() + tACIndex);

			for (auto Jp : ExistingJonctionPos)
				if ((Jp[0] == tCaseInstance->X) || (Jp[1] == tCaseInstance->Y))
					continue;

			// Top
			if (tCaseInstance->Up())
				MazePortalCases.push_back(std::make_shared<MazePortal>(tCaseInstance, MazePortal::TOP, SectionWidth));
			// Right
			else if (tCaseInstance->Right())
				MazePortalCases.push_back(std::make_shared<MazePortal>(tCaseInstance, MazePortal::RIGHT, SectionWidth));
			// Bottom
			else if (tCaseInstance->Down())
				MazePortalCases.push_back(std::make_shared<MazePortal>(tCaseInstance, MazePortal::BOTTOM, SectionWidth));
			// Left
			else if (tCaseInstance->Left())
				MazePortalCases.push_back(std::make_shared<MazePortal>(tCaseInstance, MazePortal::LEFT, SectionWidth));
			else continue;
			
			tEraseCount = 0;
			tEraseIndexes = NeighbourIndexes(tAllCases, tCaseInstance);
			for (auto V : tEraseIndexes) std::cout << V << " "; std::cout << std::endl; //DEBUG
			for (unsigned int jj = 0; jj < tEraseIndexes.size(); jj++)
			{
				tAllCases.erase(tAllCases.begin() + (tEraseIndexes[jj] - tEraseCount));
				tEraseCount++;
			}
			ii++;
		}
	}
	//*/

	//*//
	// Connect Portals
	std::vector<int> IndPortalIndexes;
	bool shouldSkip;
	for (unsigned int kk = 0; kk < MazePortalCases.size(); kk++)
		IndPortalIndexes.push_back(kk);
	for (int S = 0; S < amountOfSection - 1; S++)
	{
		shouldSkip = false;
		for (unsigned int ii = 0; ii < MazePortalCases.size(); ii++)
		{
			for (unsigned int jj = 0; jj < MazePortalCases.size(); jj++)
				if (ii != jj)
					if (MazePortalCases[ii]->GetSection() == S && MazePortalCases[jj]->GetSection() == S + 1)
						if (Contain(IndPortalIndexes, ii) && Contain(IndPortalIndexes, jj))
						{
							auto
								P1 = MazePortalCases[ii]->get(),
								P2 = MazePortalCases[jj]->get();
							Portal::Connect(P1, P2);
							IndPortalIndexes[ii] = -1; IndPortalIndexes[jj] = -1;
							shouldSkip = true;
							break;
						}
			if (shouldSkip)
				break;
		}
	}
	for (unsigned int kk = 0; kk < IndPortalIndexes.size(); kk)
	{
		if (IndPortalIndexes[kk] == -1)
			IndPortalIndexes.erase(IndPortalIndexes.begin() + kk);
		else kk++;
	}
	int tPEraseI1, tPEraseI2;
	while (!IndPortalIndexes.empty())
	{
		if (IndPortalIndexes.size() == 1)
			break;
		tPEraseI1 = std::rand() % IndPortalIndexes.size();
		tPEraseI2 = std::rand() % IndPortalIndexes.size();
		if (tPEraseI1 == tPEraseI2)
			continue;
		auto
			P1 = MazePortalCases[IndPortalIndexes[tPEraseI1]]->get(),
			P2 = MazePortalCases[IndPortalIndexes[tPEraseI2]]->get();
		Portal::Connect(P1, P2);
		IndPortalIndexes.erase(IndPortalIndexes.begin() + tPEraseI1);
		IndPortalIndexes.erase(IndPortalIndexes.begin() + (GH_MAX<int>(tPEraseI2 - 1, 0)));
	}
	//*/

	// Set Content Members
	for (int S = 0; S < nS; S++)
		for (int Y = 0; Y < H; Y++)
			for (int X = 0; X < W; X++)
				m_Rooms.push_back(Board[S][Y][X]);
	for (int INDEX = 0; INDEX < MazePortalCases.size(); INDEX++)
		m_Portals.push_back(MazePortalCases[INDEX]->get());
}


// Maze: Apply and Push each Objects/Portals to Parameters
void Maze::Apply(PObjectVec & Objects)
{
	// Push Grounds
	for (int ii = 0; ii < amountOfSection; ii++)
	{
		auto Floor = std::make_shared<Ground>();
		Floor->m_scale = Vector3(SectionWidth * 2.5f, 1.0f, SectionHeight * 2.5f);
		Floor->m_pos += Vector3((SectionWidth + 1) * ii * 5.0f + (SectionWidth - 1) * 2.5f, 0, (SectionHeight - 1) * 2.5f);
		Objects.push_back(Floor);
	}

	// Push Rooms
	for (auto M : m_Rooms)
	{
		M->Translate(Vector3(5.0f * M->X, 0, 5.0f * M->Y));
		M->Translate(Vector3(M->Section * 5.0f * (SectionWidth + 1), 0, 0));
		Objects.push_back(M->get());
	}

	// Push Portals
	for (auto P : m_Portals)
	{
		Objects.push_back(P);
	}
}


// Maze: Verify that Value is Contained in Ref
bool Maze::Contain(std::vector<int> ref, int value)
{
	for (auto I : ref)
		if (I == value)
			return true;
	return false;
}


// Maze: Return Indexes of Each Neighbours in Content
std::vector<int> Maze::NeighbourIndexes(PMazeVec Content, std::shared_ptr<MazeCase> Instance, bool checkIfOpened)
{
	std::vector<int> res;
	for (unsigned int ii = 0; ii < Content.size(); ii++)
	{
		// Top
		if (((Instance->X == Content[ii]->X)
			&& (Instance->Y == Content[ii]->Y + 1)
			&& (checkIfOpened ? Instance->Up() : true))
		// Right
			|| ((Instance->X == Content[ii]->X - 1)
				&& (Instance->Y == Content[ii]->Y)
				&& (checkIfOpened ? Instance->Right() : true))
		// Bottom
			|| ((Instance->X == Content[ii]->X)
				&& (Instance->Y == Content[ii]->Y - 1)
				&& (checkIfOpened ? Instance->Down() : true))
		// Left
			|| ((Instance->X == Content[ii]->X + 1)
				&& (Instance->Y == Content[ii]->Y)
				&& (checkIfOpened ? Instance->Up() : true)))
		{
			res.push_back((int)ii);
		}
	}
	return res;
}


// ---------- ---------- ---------- ---------- ---------- //


// MazePortal: Constructor
MazePortal::MazePortal(std::shared_ptr<MazeCase> ref, DIRECTION dir, int sectionWidth)
	: m_Content(std::make_shared<Portal>())
	, m_Parent(ref)
	, m_Direction((TYPE)((int)dir % 2))
{
	switch (dir)
	{
	case 0: m_LocalOffset = Vector3(0, 2.5f, -2.5f); break;
	case 1: m_LocalOffset = Vector3(-2.5f, 2.5f, 0); break;
	case 2: m_LocalOffset = Vector3(0, 2.5f, 2.5f); break;
	case 3: m_LocalOffset = Vector3(2.5f, 2.5f, 0); break;
	default: break;
	}
	m_Content->m_euler = Vector3(0, float(m_Direction) * GH_PI / 2.0f, 0);
	m_Content->m_scale = Vector3(1.25f, 2.5f, 1.25f);
	m_Content->m_pos =
		m_LocalOffset // Local Offset Member
		+ Vector3(5.0f * m_Parent->X, 0, 5.0f * m_Parent->Y) // Case Offset
		+ Vector3(GetSection() * 5.0f * (sectionWidth + 1), 0, 0); // Section Offset
}
