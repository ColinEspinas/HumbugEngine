#include "HumbugEngine/BallPhysic.h"

BallPhysic::BallPhysic(Entity* phy)
	: PhysicRuleset(phy)
{
	/// TODO
	// Add hit Sphere
}

void BallPhysic::PerReset()
{
	onGround = false;
	curFriction = 0.0f;
}

void BallPhysic::PerFrame()
{
	/// TODO
	// Slow on Movement with Friction
}

Vector3 BallPhysic::PerHit(Object & other, const Vector3 & push)
{
	/// TODO
	return Vector3();
}

void BallPhysic::Move(float h, float v)
{
	//Make sure movement is not too fast
	const float mag = std::sqrt(h*h + v*v);
	if (mag > 1.0f) {
		h /= mag;
		v /= mag;
	}

	/// TO CHANGE
	//Movement
	///const Matrix4 camToWorld = LocalToWorld() * Matrix4::RotY(cam_ry);
	///body->velocity += camToWorld.MulDirection(Vector3(-h, 0, -v)) * (GH_WALK_ACCEL * GH_DT);

	//Don't allow non-falling speeds above the player's max speed
	const float tempY = body->velocity.y;
	body->velocity.y = 0.0f;
	body->velocity.ClipMag(body->p_scale * GH_WALK_SPEED);
	body->velocity.y = tempY;
}
