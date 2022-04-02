#pragma once
#include <string>
#include "Vector.h"

using namespace std;
class BaseObject;

class BaseEvent
{
protected:
	string EventType;
public:
	~BaseEvent() { }
	string returnType(){ return EventType; }
};

class QuitEvent : public BaseEvent {
public:
	QuitEvent() { EventType = "Quit"; }
};

class KeyInput : public BaseEvent {
protected:
	bool keyDown;
public:
	KeyInput(bool keyDown_) { keyDown = keyDown_; }
	bool GetKeyDown() { return keyDown; }
};

class UpInput : public KeyInput {
public:
	UpInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Up"; }
};

class LeftInput : public KeyInput {
public: 
	LeftInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Left"; }
};

class RightInput : public KeyInput {
public:
	RightInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Right"; };
};

class EscapeInput : public KeyInput {
public:
	EscapeInput(bool keyDown_) : KeyInput(keyDown_) { EventType = "Escape"; }
};

class LMBInput : public KeyInput {
protected:
	float x;
	float y;
public:
	LMBInput(bool keyDown_, float x_, float y_) : KeyInput(keyDown_) { EventType = "LMB"; x = x_; y = y_; };
	Vector2f GetMousePos();
};