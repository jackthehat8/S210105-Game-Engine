#pragma once
#include "Events.h"
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;
class EventManager
{
private:
	vector<BaseEvent*> events;

	static EventManager* eventManager;

	map<size_t, vector<GameObject*>> listeners;

	//referenced from: https://stackoverflow.com/questions/8029121/how-to-hash-stdstring
	size_t hashString(string stringToHash);
	//end of reference

public:
	EventManager() {}
	~EventManager() { delete this; }

	static EventManager* GetInstance();

	void AddListener(string eventType, GameObject* object);
	void QueueEvent(BaseEvent* event);
	void FireEvents();
};

