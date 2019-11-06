#include "HumbugEngine/Physics/Playable.h"
#include "HumbugEngine/Core/Input.h"
#include "HumbugEngine/Utils/GameHeader.h"
#include "HumbugEngine/Utils/Vector.h"
#include "HumbugEngine/Components/Camera.h"

// Update Function
void Playable::Update()
{
	//Looking
	Look(GH_INPUT->mouse_dx, GH_INPUT->mouse_dy);

	//Movement
	float moveF = 0.0f;
	float moveL = 0.0f;
	if (GH_INPUT->key['Z']) {
		moveF += 1.0f;
	}
	if (GH_INPUT->key['S']) {
		moveF -= 1.0f;
	}
	if (GH_INPUT->key['Q']) {
		moveL += 1.0f;
	}
	if (GH_INPUT->key['D']) {
		moveL -= 1.0f;
	}
	Move(moveF, moveL);
}

// Reset Values
void Playable::Reset()
{
	cam_rx = 0;
	cam_ry = 0;
}

// Looking Action
void Playable::Look(float mouseDx, float mouseDy)
{
	//Adjust x-axis rotation
	cam_rx -= mouseDy * GH_MOUSE_SENSITIVITY;
	if (cam_rx > GH_PI / 2) {
		cam_rx = GH_PI / 2;
	}
	else if (cam_rx < -GH_PI / 2) {
		cam_rx = -GH_PI / 2;
	}

	//Adjust y-axis rotation
	cam_ry -= mouseDx * GH_MOUSE_SENSITIVITY;
	if (cam_ry > GH_PI) {
		cam_ry -= GH_PI * 2;
	}
	else if (cam_ry < -GH_PI) {
		cam_ry += GH_PI * 2;
	}
}
