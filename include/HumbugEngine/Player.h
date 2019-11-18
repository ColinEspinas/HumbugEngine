#pragma once
#include "HumbugEngine/Vector.h"
#include "HumbugEngine/Physical.h"
#include "HumbugEngine/Playable.h"

#include "PointLight.h"

static const float PLAYER_RUNNING_MULTIPLIER = 1.7f;

class Player : public Physical, public Playable {
public:
  Player();
  virtual ~Player() override {}

  virtual void Reset() override;
  virtual void Update() override;
  virtual void OnCollide(Object& other, const Vector3& push) override;

  virtual void Move(float moveF, float moveL) override;

  virtual Matrix4 WorldToCam() const override;
  virtual Matrix4 CamToWorld() const override;
  virtual Vector3 CamOffset() const override;

  virtual int Cast() const override { return 1; }

  std::shared_ptr<PointLight> getTorch() const { return Torch; }

private:

  float bob_mag;
  float bob_phi;

  std::shared_ptr<PointLight> Torch;

  bool onGround;
};
