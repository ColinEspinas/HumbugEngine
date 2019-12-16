#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"
#include "HumbugEngine/Animator.h"
#include "HumbugEngine/Sequence.h"

class JellyFish : public Object
{
private:
    std::shared_ptr<Sequence> sequence;

public:
    JellyFish()
    {
        mesh = AquireMesh("jellyfish.obj");
        shader = AquireShader("texture");
        texture = AquireTexture("white.bmp");

        sequence = AquireSequence("jellyfishanim");
        sequence->Apply(animator);


    }
    virtual ~JellyFish() {}
};