#include "Player.h"
#include "Sprite.h"
#include <iostream>

using namespace std;

Player::Player(BaseObject* owner_)
{
	Player* temp = this;
	health = maxHealth;
	owner = owner_;

}

void Player::jump()
{
}

void Player::resetPlayer()
{
	health = maxHealth;
	left = false;
	right = false;
	((Physics*)owner->GetComponent(PHYSICS))->SetForces({ 0,0 });
	if (currentCheckpoint != nullptr) {
		Vector2f temp = ((Transform*)currentCheckpoint->GetComponent(TRANSFORM))->GetGlobalPos();
		((Transform*)owner->GetComponent(TRANSFORM))->SetPosition(((Transform*)currentCheckpoint->GetComponent(TRANSFORM))->GetGlobalPos() - ((Transform*)ObjectManager::GetInstance()->GetSceneRoot()->GetComponent(TRANSFORM))->GetGlobalPos());
	}

}

void Player::EndLevel()
{
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

	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForCollisions()) {
		if (object->HasTag("Enemy"))
			Damage(1);
	}

	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForOverlaps()) {
		if (object->HasTag("Checkpoint"))
			currentCheckpoint = object;
		else if (object->HasTag("Key")) {
			hasKey = true;
			((Sprite*)object->GetComponent(SPRITE))->SetVisability(false);
		}
		else if (object->HasTag("EndDoor") && hasKey)
			EndLevel();
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

void Player::Damage(int value)
{
	health -= value;
	if (health <= 0)
		resetPlayer();
}
