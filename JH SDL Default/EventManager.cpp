#include "EventManager.h"
#include "BaseObject.h"

EventManager* EventManager::eventManager = NULL;

EventManager* EventManager::GetInstance()
{
    //creates a new instance of EventManager if one does not exist to be referenced
    if (eventManager == NULL)
        eventManager = new EventManager();
    return eventManager;
}

//referenced from: https://stackoverflow.com/questions/8029121/how-to-hash-stdstring
size_t EventManager::hashString(string stringToHash)
{
    hash<string> hasher;

    return hasher(stringToHash);
}//end of reference

/// <summary>
/// Adds a listener to the chosen event type
/// </summary>
void EventManager::AddListener(string eventType, BaseObject* object)
{
    //get the key to the map
    size_t hashedKey = hashString(eventType);

    //check if the map location already exist to be added to
    if (listeners.find(hashedKey) == listeners.end())
    {
        //if it doesnt exist a new location in the map is made
        vector<BaseObject*> newListenerType;
        listeners.insert(pair<size_t, vector<BaseObject*>>(hashedKey, newListenerType));
    }
    //the listener is added to the map
    listeners.find(hashedKey)->second.push_back(object);
}

void EventManager::QueueEvent(BaseEvent* event)
{
    //adds a new event to be called that frame
    events.push_back(event);
}

void EventManager::FireEvents()
{
    //calls all events that were added this frame
    while(events.size() > 0){
        //gets the key from the produced event
        BaseEvent* currentEvent = events[0];
        //makes it into the key for the map
        size_t hashKey = hashString(currentEvent->returnType());

        //checks if that key exists in the map
        if (listeners.find(hashKey) != listeners.end()) {
            //loop through all the listeners and give them the data
            for (BaseObject* currentObject : listeners.find(hashKey)->second) {
                currentObject->HandleEvent(currentEvent);
              }
        }
        //remove the current event 
        events.erase(events.begin());
        delete currentEvent;
        
   }
    //clear out the whole queue
    events.clear();
}
