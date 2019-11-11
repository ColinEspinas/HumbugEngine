#include "HumbugEngine/Objects/LightObject.h"

// Default Constructor
template <typename L> LightObject::LightObject(bool genLight)
{
    if (genLight)
        AddComponent<L>();
}