#pragma once
#include "HumbugEngine/Object.h"
#include "HumbugEngine/Resources.h"
#include "HumbugEngine/Animator.h"
#include "HumbugEngine/Sequence.h"

class Car : public Object
{
private:
    std::shared_ptr<Sequence> sequence;

public:
    Car()
    {
        mesh = AquireMesh("FiatUNO.obj");
        shader = AquireShader("texture");
        texture = AquireTexture("white.bmp");

        // sequence = AquireSequence("test");
        // sequence->Apply(animator);

        // animator->LoopAll();
        // animator->Build({
        //     { {0,2}, {{0,-8},{3,8},{6,8},{9,-8},{12,-8}} },
        //     { {0,0}, {{0,-8},{3,-8},{6,8},{9,8},{12,-8}} },

        //     { {1,1}, {{0,0},{2.8,0},{3.2,1.571},{5.8,1.571},
        //     {6.2,3.142},{8.8,3.142},{9.2,4.712},{11.8,4.712},{12,6.283}} }
        // });
    }
    virtual ~Car() {}
};