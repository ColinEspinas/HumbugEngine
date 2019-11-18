#pragma once
#include "HumbugEngine/Utils/Vector.h"
#include "HumbugEngine/Physics/Physical.h"
#include "HumbugEngine/Physics/Playable.h"

#include "HumbugEngine/Components/PointLight.h"
#include "HumbugEngine/Objects/LightObject.h"

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

  std::shared_ptr<LightObject> getTorch() { return Torch; }

private:

  float bob_mag;
  float bob_phi;

  std::shared_ptr<LightObject> Torch;

  bool onGround;
};
