#pragma once
#include "HumbugEngine/Animator.h"

Animator::Animator():
index(0)
{
	for (int ii = 0; ii < 3; ++ii) {
		m_lstAnim.push_back(std::vector<Animation>(3));
	}
	timer.Start();
}

void Animator::addTransformAnimation(Animation anim) {
	m_lstAnim[0].push_back(anim);
}
void Animator::addRotationAnimation(Animation anim) {
	m_lstAnim[1].push_back(anim);
}
void Animator::addScaleAnimation(Animation anim) {
	m_lstAnim[2].push_back(anim);
}

void Animator::Update(std::shared_ptr<Object> obj) {
	for (int jj; jj < m_lstAnim.size(); ++jj) {
		if (timer.GetTicks() == m_lstAnim[0][0].getKey(jj).getTimeStamp()) {

		}
	}
	//update Obj TODO
	//Vector3 buffer;
	//for (int jj; jj < 3; ++jj) {

	//	buffer.x = m_lstAnim[0][0].getKey(index);
	//}

	//obj.scale = buffer;
	//++index;
}
