#pragma once
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "EventManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "Time.h"


/// This contains the differnt managers and generates an instance of them
///
/// This is a singleton
class System
{
private:
	/// The Time instance
	Time* timer;

	/// The System instance
	static System* instance;

	/// The EventManager instance
	EventManager* eventManager;

	/// The ScreenManager instance
	ScreenManager* screen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	/// The Input instance
	Input* inputManager;

	/// The ObjectManager instance
	ObjectManager* objectManager;

	/// The ResourceManager instance
	ResourceManager* resourceManager;

public:
	/// Generates the instances of each manager
	System();
	/// Destroys all of the managers by calling thier deconstructors
	~System();

	/// Gets the instance of System
	static System* GetInstance();

	/// Gets the ScreenManager
	ScreenManager* GetScreenManager() { return screen; }
	/// Gets the ObjectManager
	ObjectManager* GetObjectManager() { return objectManager; }
	/// Gets the ResourceManager
	ResourceManager* GetResourceManager() { return resourceManager; }
	/// Gets the EventManager
	EventManager* GetEventManager() { return eventManager; }
	/// Gets the Input
	Input* GetInputManager() { return inputManager; }
};

