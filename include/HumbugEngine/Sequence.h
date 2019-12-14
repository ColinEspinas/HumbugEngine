#pragma once
#include <string>
#include <array>
#include "HumbugEngine/Animation.h"
#include "HumbugEngine/Animator.h"

class Sequence
{
private:
    std::array<std::array<std::vector<std::array<float,2>>,3>,3> saved_Keys;
    std::array<std::array<std::array<bool,2>,3>,3> saved_Config;

    int tMethod, tAxis;
    int ComputeIndex(int method, int axis);

public:
    Sequence(std::string fname);
    void Apply(std::shared_ptr<Animator> anim);
};