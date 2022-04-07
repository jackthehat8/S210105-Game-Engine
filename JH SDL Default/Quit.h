#pragma once
#include "BaseScript.h"
class Quit :
    public BaseScript
{
private:
    BaseObject* owner;
public:
    /// sets it owner to listen for a QuitEvent
    Quit(BaseObject* owner_);
    /// listens for a QuitEvent and will run Game::Quit()
    /// <param name="event"></param>
    void HandleEvent(BaseEvent* event);
};

