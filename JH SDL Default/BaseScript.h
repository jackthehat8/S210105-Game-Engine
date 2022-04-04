#pragma once
#include "BaseComponent.h"
#include "Vector.h"
#include "Events.h"
#include "Physics.h"
#include "Transform.h"
class BaseScript :
    public BaseComponent
{
protected:
    BaseScript() { type = SCRIPT; }
};

