#pragma once
#include "Events.h"
#include <vector>
#include <unordered_map>
#include <map>

using namespace std;
class EventManager
{
private:

	/// the list of events that havent be fired yet
	vector<BaseEvent*> events;

	/// stores the EventManager instance
	static EventManager* eventManager;

	/// stores the listeners for each event type
	map<size_t, vector<BaseObject*>> listeners;

	/// makes a hashed string
	/// 
	/// referenced from: https://stackoverflow.com/questions/8029121/how-to-hash-stdstring
	/// <param name="stringToHash">the string to be hashed</param>
	/// <returns>a hashed string</returns>
	size_t hashString(string stringToHash);
	//end of reference

public:
	/// nothing is constructed as values are defualted
	EventManager() {}
	/// destroyes itself
	~EventManager() {}

	/// gets the EventManager instance
	static EventManager* GetInstance();

	/// adds a BaseObject to listen for a event type
	/// <param name="eventType">the key for the event type</param>
	/// <param name="object">the BaseObject that is to be added as a listener</param>
	void AddListener(string eventType, BaseObject* object);

	/// add a event to be called in FireEvents()
	/// <param name="event">the event to be added</param>
	void QueueEvent(BaseEvent* event);

	/// Fires the events that have been queued
	/// 
	/// The first event in the queue is taken and sampled
	/// the listeners are got from the map and the HandleEvent() function is called for each BaseObject
	/// once called it is removed from the queue and the next is called
	void FireEvents();
};

