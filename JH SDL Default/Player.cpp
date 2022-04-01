#include "Player.h"
#include "Events.h"
#include "Physics.h"
#include "Transform.h"

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

void Player::update()
{

	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForOverlaps()) {
		if (object->HasTag("Platform"))
			landed = true;
	}

	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForOverlaps()) {
		if (object->HasTag("Checkpoint"))
			currentCheckpoint = object;
	}
}

void Player::HandleEvent(BaseEvent* event)
{
	string eventName = event->returnType();

	if (eventName == "Left") {
		((Physics*)owner->GetComponent(PHYSICS))->AddForce(Vector2f(-moveSpeed, 0));
	}
	else if (eventName == "Right") {
		((Physics*)owner->GetComponent(PHYSICS))->AddForce(Vector2f(moveSpeed, 0));
	}
	else if (eventName == "Up" /* && landed*/) {
		((Physics*)owner->GetComponent(PHYSICS))->AddForce(Vector2f(0,-jumpForce));
		landed = false;
	}
		
}
