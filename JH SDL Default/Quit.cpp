#include "Quit.h"
#include "Game.h"
#include "EventManager.h"

Quit::Quit(BaseObject* owner_)
{
	owner = owner_;
	EventManager::GetInstance()->AddListener("Quit", owner);
}

void Quit::HandleEvent(BaseEvent* event)
{
	if (event->returnType() == "Quit") 
		Game::GetInstance()->Quit();
}
