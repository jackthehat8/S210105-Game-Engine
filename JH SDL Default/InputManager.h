#include "SDL.h"

class EventManager;

class Input {
public:
	Input();
	~Input();

	static Input* GetInstance();

	void Update();
private:
	EventManager* eventManager;
	static Input* instance;
};