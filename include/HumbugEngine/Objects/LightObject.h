#pragma once
#include "HumbugEngine/Objects/Object.h"
#include "HumbugEngine/Components/PointLight.h"

class LightObject : public Object {
public:
    LightObject(bool genLight = true);
};