#pragma once
#include <string>
#include "Vector.h"

using namespace std;
class BaseObject;


/// This is the event all other events inherit from
/// 
/// Each of the other events sets eventType in thier constructor
/// This stores a string for the event type and a function to return it
/// It itself is not used in any event call
class BaseEvent
{
protected:
	string EventType;
public:
	~BaseEvent() { }
	string returnType(){ return EventType; }
};

/// <summary>
/// This is a quit event 
/// </summary>
class QuitEvent : public BaseEvent {
public:
	///### Example
	/// ~~~~~~~~~~~~~~.cpp
	/// QuitEvent* newEvent = new QuitEvent();
	/// ~~~~~~~~~~~~~~
	QuitEvent() { EventType = "Quit"; }
};


/// This is used for all events that get a key in their funciton
/// 
/// For example: getting the 'A' key
class KeyInput : public BaseEvent {
protected:
	bool keyDown;
public:
	///### Example
	/// ~~~~~~~~~~~~~~.cpp
	/// KeyInput* newEvent = new KeyInput(true); //true = key has been pressed, false = key has been let go of
	/// ~~~~~~~~~~~~~~
	KeyInput(bool keyDown_) { keyDown = keyDown_; }
	bool GetKeyDown() { return keyDown; }
};


/// Used for an input that will make the player go up
class UpInput : public KeyInput {
public:
	UpInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Up"; }
};

/// Used for an input that will make the player go to the left
class LeftInput : public KeyInput {
public: 
	LeftInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Left"; }
};

/// Used for an input that will make the player go to the right
class RightInput : public KeyInput {
public:
	RightInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Right"; };
};

/// Used for when the escape key is pressed
class EscapeInput : public KeyInput {
public:
	EscapeInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Escape"; }
};

/// Used for when the mouse is clicked
///
/// This stores the position where the mouse was pressed
class LMBInput : public KeyInput {
protected:
	float x;
	float y;
public:
	LMBInput(bool keyDown_, float x_, float y_) : KeyInput(keyDown_) { EventType = "LMB"; x = x_; y = y_; };
	Vector2f GetMousePos() {return Vector2f(x, y);}
};