#include "Quit.h"
#include "Game.h"
#include "EventManager.h"

Quit::Quit(BaseObject* owner_)
{
	owner = owner_;
	//adds object as listener for Quit event
	EventManager::GetInstance()->AddListener("Quit", owner);
}

void Quit::HandleEvent(BaseEvent* event)
{
	// if quit event is queued it called it calls quit in game.h
	if (event->returnType() == "Quit") 
		Game::GetInstance()->Quit();
}
