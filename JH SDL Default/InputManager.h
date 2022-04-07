#include "SDL.h"

class EventManager;

class Input {
public:
	/// Gets the EventManager
	Input();
	///Has nothing to deconstruct except of itself
	~Input();

	/// Gets the instance of Input
	static Input* GetInstance();

	/// Creates events for key inputs
	/// 
	/// The SDL inputs are used to create corresponding events
	void Update();
private:
	/// stores the EvenetManager
	EventManager* eventManager;
	/// stores the Input instance
	static Input* instance;
};