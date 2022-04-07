#include "QuitButton.h"
#include "EventManager.h"

void QuitButton::ButtonPressed()
{
	//queues a new quit event
	EventManager::GetInstance()->QueueEvent(new QuitEvent());
}
