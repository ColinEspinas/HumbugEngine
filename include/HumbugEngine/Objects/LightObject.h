#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Components/Light.h"

class LightObject : public Object {
public:
    template <typename L = Light>
    LightObject(bool genLight = true);
};