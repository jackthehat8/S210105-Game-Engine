#pragma once
#include <string>
#include "Vector.h"

using namespace std;
class GameObject;

class BaseEvent
{
protected:
	string EventType;
public:
	~BaseEvent() { }
	string returnType(){ return EventType; }
};

class QuitEvent : public BaseEvent {
protected:
	string EventType = "Quit";
};

class KeyInput : public BaseEvent {
protected:
	bool keyDown;
public:
	KeyInput(bool keyDown_) { keyDown = keyDown_; }
	bool GetKeyDown() { return keyDown; }
};

class UpInput : public KeyInput {
protected:
	string EventType = "Up";
public:
	UpInput(bool keyDown_) : KeyInput(keyDown_) {};
};

class LeftInput : public KeyInput {
protected:
	string EventType = "Left";
public: 
	LeftInput(bool keyDown_) : KeyInput(keyDown_) {};
};

class RightInput : public KeyInput {
protected:
	string EventType = "Right";
public:
	RightInput(bool keyDown_) : KeyInput(keyDown_) {};
};

class EscapeInput : public KeyInput {
protected:
	string EventType = "Escape";
public:
	EscapeInput(bool keyDown_) : KeyInput(keyDown_) {};
};

class LMBInput : public KeyInput {
protected:
	string EventType = "LMB";
	float x;
	float y;
public:
	LMBInput(bool keyDown_, float x_, float y_) : KeyInput(keyDown_) { x = x_; y = y_; };
	Vector2f GetMousePos();
};