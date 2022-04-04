#include "System.h"
#include "Constants.h"

System* System::instance = NULL;

System::System() {

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	
	//creates a new screen
	screen = ScreenManager::GetInstance(); 
	m_window = screen->getWindow();
	m_renderer = screen->getRenderer();

	timer = Time::GetInstance();

	eventManager = EventManager::GetInstance();
	objectManager = ObjectManager::GetInstance();
	inputManager = Input::GetInstance();

	//creates an instance of the resource manager
	resourceManager = ResourceManager::GetInstance();
}

System::~System()
{
	//destroys the managers and itself
	resourceManager->~ResourceManager();
	screen->~ScreenManager();
	eventManager->~EventManager();
}

System* System::GetInstance()
{
	//creates a new System class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new System();
	return instance;
}
