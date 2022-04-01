#pragma once
#include "BaseComponent.h"
#include "Vector.h"
class BaseScript :
    public BaseComponent
{
protected:
    BaseScript() { type = SCRIPT; }
};

