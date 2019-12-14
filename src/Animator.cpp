#pragma once
#include "HumbugEngine/Animator.h"

Animator::Animator(Object* obj, int id)
	: index(id), localTimer(0)
{
	m_target = obj;
	for (int ii = 0; ii < 3; ++ii)
		for (int jj = 0; jj < 3; ++jj)
			m_lstAnim[ii][jj] = std::make_shared<Animation>();
}

void Animator::Update()
{
	// Increment Timer
	localTimer += GH_DT;
	//std::cout << "Time: " << localTimer << std::endl; //DEBUG

	for (int ii = 0; ii < 3; ++ii)
		for (int jj = 0; jj < 3; ++jj)
			if (m_lstAnim[ii][jj]->canRun())
			{
				//std::cout << ii << " " << jj << std::endl; //DEBUG
				switch (ii * 3 + jj)
				{
					// Translation
				case 0: m_target->pos.x = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 1: m_target->pos.y = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 2: m_target->pos.z = m_lstAnim[ii][jj]->getValue(localTimer); break;

					// Rotation
				case 3: m_target->euler.x = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 4: m_target->euler.y = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 5: m_target->euler.z = m_lstAnim[ii][jj]->getValue(localTimer); break;

					// Scale
				case 6: m_target->scale.x = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 7: m_target->scale.y = m_lstAnim[ii][jj]->getValue(localTimer); break;
				case 8: m_target->scale.z = m_lstAnim[ii][jj]->getValue(localTimer); break;

				default: break;
				}
			}
}

void Animator::Build(std::vector<std::pair<std::array<int,2>,std::vector<std::array<float,2>>>> content)
{
	for (auto anim : content)
		if (anim.first[0] >= 0 && anim.first[0] < 3
			&& anim.first[1] >= 0 && anim.first[0] < 3)
			for (auto key : anim.second)
				m_lstAnim[anim.first[0]][anim.first[1]]->AddKey(key[0], key[1]);
}

std::shared_ptr<Animation> Animator::getAnimation(AnimationType::METHOD _m, AnimationType::AXIS _a)
{
	return m_lstAnim[(int)_m][(int)_a];
}

void Animator::LoopAll(bool state)
{
	for (int ii = 0; ii < 3; ++ii)
		for (int jj = 0; jj < 3; ++jj)
			m_lstAnim[ii][jj]->loop = state;
}
