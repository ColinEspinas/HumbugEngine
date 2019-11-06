#include "HumbugEngine/Objects/Player.h"
#include "HumbugEngine/Core/Input.h"
#include "HumbugEngine/Utils/GameHeader.h"
#include <Windows.h>
#include <iostream>

Player::Player() {
	Torch = std::make_shared<PointLight>(m_pos + Vector3(0, GH_PLAYER_HEIGHT / 2, 0), 1.0f, 0.09f, 0.032f, Vector3(1.0f, 1.0f, 1.0f), Vector3(1.0f, 0.8f, 0.8f));
	Reset();
	hitSpheres.push_back(Sphere(Vector3(0, 0, 0), GH_PLAYER_RADIUS));
	hitSpheres.push_back(Sphere(Vector3(0, GH_PLAYER_RADIUS - GH_PLAYER_HEIGHT, 0), GH_PLAYER_RADIUS));
}

void Player::Reset() {
  Physical::Reset();
  Playable::Reset();
  bob_mag = 0.0f;
  bob_phi = 0.0f;
  friction = 0.04f;
  drag = 0.002f;
  Torch->MoveTo(m_pos + Vector3(0, GH_PLAYER_HEIGHT / 2, 0));
  onGround = true;
}

void Player::Update() {
  //Update bobbing motion
  float magT = (prev_pos - m_pos).Mag() / (GH_DT * p_scale);
  if (!onGround) { magT = 0.0f; }
  bob_mag = bob_mag*(1.0f - GH_BOB_DAMP) + magT*GH_BOB_DAMP;
  if (bob_mag < GH_BOB_MIN) {
    bob_phi = 0.0f;
  } else {
	  bob_phi += GH_BOB_FREQ * GH_DT;
    if (bob_phi > 2 * GH_PI) {
      bob_phi -= 2 * GH_PI;
    }
  }

  //Physics
  Physical::Update();

  //Playable
  Playable::Update();

  // Switch On/Off Torch
  if (GH_INPUT->key_press['F'])
	  Torch->On = !Torch->On;

  //Update Torch Position
  Torch->MoveTo(m_pos + Vector3(0, GH_PLAYER_HEIGHT / 2, 0));

#if 0
  //Running
  if (GH_INPUT->key[VK_SHIFT]) {
	  velocity.x *= PLAYER_RUNNING_MULTIPLIER;
	  velocity.z *= PLAYER_RUNNING_MULTIPLIER;
  }
#endif

  //Jumping
  if (onGround && GH_INPUT->key[VK_SPACE]) {
    velocity.y += 2.0f * p_scale;
  }

  //Reset ground state after update finishes
  onGround = false;
}

void Player::OnCollide(Object& other, const Vector3& push) {
  //Prevent player from rolling down hills if they're not too steep
  Vector3 newPush = push;
  if (push.Normalized().y > 0.7f) {
    newPush.x = 0.0f;
    newPush.z = 0.0f;
    onGround = true;
  }

  //Friction should only apply when player is on ground
  const float cur_friction = friction;
  if (!onGround) {
    friction = 0.0f;
  }

  //Base call
  Physical::OnCollide(other, newPush);
  friction = cur_friction;
}

void Player::Move(float moveF, float moveL)
{
	//Make sure movement is not too fast
	const float mag = std::sqrt(moveF*moveF + moveL * moveL);
	if (mag > 1.0f) {
		moveF /= mag;
		moveL /= mag;
	}

	//Movement
	const Matrix4 camToWorld = LocalToWorld() * Matrix4::RotY(cam_ry);
	velocity += camToWorld.MulDirection(Vector3(-moveL, 0, -moveF)) * (GH_WALK_ACCEL * GH_DT);

	//Don't allow non-falling speeds above the player's max speed
	const float tempY = velocity.y;
	velocity.y = 0.0f;
	velocity.ClipMag(p_scale * GH_WALK_SPEED);
	velocity.y = tempY;
}

Matrix4 Player::WorldToCam() const {
  return Matrix4::RotX(-cam_rx) * Matrix4::RotY(-cam_ry) * Matrix4::Trans(-CamOffset()) * WorldToLocal();
}

Matrix4 Player::CamToWorld() const {
  return LocalToWorld() * Matrix4::Trans(CamOffset()) * Matrix4::RotY(cam_ry) * Matrix4::RotX(cam_rx);
}

Vector3 Player::CamOffset() const {
  //If bob is too small, don't even bother
  if (bob_mag < GH_BOB_MIN) {
    return Vector3::Zero();
  }

  //Convert bob to translation
  const float theta = (GH_PI/2) * std::sin(bob_phi);
  const float y = bob_mag * GH_BOB_OFFS * (1.0f - std::cos(theta));
  return Vector3(0, y, 0);
}
