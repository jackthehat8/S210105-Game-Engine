#include "Player.h"
#include "Events.h"
#include "Physics.h"
#include "Transform.h"
#include <iostream>

using namespace std;

void Player::jump()
{
}

void Player::resetPlayer()
{
	health = maxHealth;
	((Transform*)owner->GetComponent(TRANSFORM))->SetPosition(((Transform*)currentCheckpoint->GetComponent(TRANSFORM))->GetGlobalPos());

}

Player::Player(BaseObject* owner_)
{
	Player* temp = this;
	owner = owner_;

}

void Player::Update()
{
	Physics* physics = (Physics*)owner->GetComponent(PHYSICS);
	if(left)
		physics->SetXForce(-moveSpeed);
	else if(right)
		physics->SetXForce(moveSpeed);
	else
		physics->SetXForce(0);
	
	onPlatform = (physics->GetForces().y == 0);

	cout << physics->GetForces().y << endl;

	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForOverlaps()) {
		if (object->HasTag("Checkpoint"))
			currentCheckpoint = object;
	}
}

void Player::HandleEvent(BaseEvent* event)
{
	KeyInput* eventKey = (KeyInput*)event;
	string eventName = event->returnType();

	if (eventName == "Left")
		left = eventKey->GetKeyDown();
	else if (eventName == "Right")
		right = eventKey->GetKeyDown();
	else if (eventName == "Up"  && onPlatform) {
		((Physics*)owner->GetComponent(PHYSICS))->AddForce(Vector2f(0,-jumpForce));
		onPlatform = false;
	}
		
}
