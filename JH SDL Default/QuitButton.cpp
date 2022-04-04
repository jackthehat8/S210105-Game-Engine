#include "QuitButton.h"
#include "EventManager.h"

void QuitButton::ButtonPressed()
{
	EventManager::GetInstance()->QueueEvent(new QuitEvent());
}
