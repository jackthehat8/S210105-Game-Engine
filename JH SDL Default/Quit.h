#pragma once
#include "BaseScript.h"
class Quit :
    public BaseScript
{
private:
    BaseObject* owner;
public:
    Quit(BaseObject* owner_);
    void HandleEvent(BaseEvent* event);
};

