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
    /// this sets the type equal to Script so that is is stored in the correct place when used in AddComponent
    /// @see BaseObject::AddComponent(BaseComponent* component)
    BaseScript() { type = SCRIPT; }
};

