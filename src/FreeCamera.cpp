#include "HumbugEngine/FreeCamera.h"
#include "HumbugEngine/Utils/GameHeader.h"
#include "HumbugEngine/Core/Input.h"
#include <Windows.h>

void FreeCamera::Reset()
{
	Velocity = Vector3(0.0f);
	Playable::Reset();
}

void FreeCamera::Update()
{
	if (!GH_INPUT->key['Z']
		&& !GH_INPUT->key['D']
		&& !GH_INPUT->key['S']
		&& !GH_INPUT->key['Q'])
		Velocity = Vector3(0.0f);

	if (GH_INPUT->key[VK_SPACE])
		Velocity.y = FREECAMERA_VERTICAL_VELOCITY;
	else if (GH_INPUT->key[VK_SHIFT])
		Velocity.y = -FREECAMERA_VERTICAL_VELOCITY;
	else Velocity.y = 0.0f;

	m_pos += Velocity * GH_DT * FREECAMERA_SPEED_MULTIPLIER;
	Playable::Update();
}

void FreeCamera::Move(float moveF, float moveL)
{
	//Make sure movement is not too fast
	const float mag = std::sqrt(moveF*moveF + moveL * moveL);
	if (mag > 1.0f) {
		moveF /= mag;
		moveL /= mag;
	}

	//Movement
	const Matrix4 camToWorld = LocalToWorld() * Matrix4::RotY(cam_ry);
	Velocity += camToWorld.MulDirection(Vector3(-moveL, 0, -moveF)) * (GH_WALK_ACCEL * GH_DT);

	//Don't allow non-falling speeds above the player's max speed
	const float tempY = Velocity.y;
	Velocity.y = 0.0f;
	Velocity.ClipMag(p_scale * GH_WALK_SPEED);
	Velocity.y = tempY;
}

Matrix4 FreeCamera::WorldToCam() const
{
	return Matrix4::RotX(-cam_rx) * Matrix4::RotY(-cam_ry) * Matrix4::Trans(-CamOffset()) * WorldToLocal();
}

Matrix4 FreeCamera::CamToWorld() const
{
	return LocalToWorld() * Matrix4::Trans(CamOffset()) * Matrix4::RotY(cam_ry) * Matrix4::RotX(cam_rx);
}

Vector3 FreeCamera::CamOffset() const
{
	return Vector3(0.0f);
}
