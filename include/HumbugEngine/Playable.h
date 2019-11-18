#pragma once
#include "HumbugEngine/Object.h"
#include <array>

class Playable
{
public:

	Playable() : cam_rx(0.0f), cam_ry(0.0f) {}

	std::array<float, 2> get_Orientation() const { return { cam_rx,cam_ry }; }

	virtual void Update();
	virtual void Reset();

	virtual void Look(float mouseDx, float mouseDy);
	virtual void Move(float moveF, float moveL) = 0;

	virtual Matrix4 WorldToCam() const = 0;
	virtual Matrix4 CamToWorld() const = 0;
	virtual Vector3 CamOffset() const = 0;

	virtual int Cast() const = 0;

protected:

	float cam_rx;
	float cam_ry;
};