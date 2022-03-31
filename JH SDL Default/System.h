#pragma once
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Time.h"

class System
{
private:
	Time* timer;

	static System* instance;

	EventManager* eventManager;

	ScreenManager* screen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	Input* inputManager;

	ObjectManager* objectManager;

	ResourceManager* resourceManager;

public:
	System();
	~System();

	static System* GetInstance();

	ScreenManager* GetScreenManager() { return screen; }
	ObjectManager* GetObjectManager() { return objectManager; }
	ResourceManager* GetResourceManager() { return resourceManager; }
	EventManager* GetEventManager() { return eventManager; }
	Input* GetInputManager() { return inputManager; }
};

