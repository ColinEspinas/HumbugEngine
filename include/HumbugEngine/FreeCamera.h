#pragma once
#include "HumbugEngine/Physics/Playable.h"
#include "HumbugEngine/Utils/Vector.h"

static const float FREECAMERA_SPEED_MULTIPLIER = 2.0f;
static const float FREECAMERA_VERTICAL_VELOCITY = 1.5f;

class FreeCamera : public Playable, public Object
{
public:

	FreeCamera() : Velocity({0.0f}) {}

	virtual void Reset() override;
	virtual void Update() override;

	virtual void Move(float moveF, float moveL) override;

	virtual Matrix4 WorldToCam() const override;
	virtual Matrix4 CamToWorld() const override;
	virtual Vector3 CamOffset() const override;

	virtual int Cast() const override { return 2; }

private:

	Vector3 Velocity;
};
