#include "Player.h"
#include "Sprite.h"
#include <iostream>
#include "SceneManager.h"
#include "EventManager.h"

using namespace std;

Player::Player(BaseObject* owner_)
{
	Player* temp = this;
	health = maxHealth;
	owner = owner_;

	//add the object to listen for the Left, Right and Up events
	EventManager* eventManager = EventManager::GetInstance();
	eventManager->AddListener("Left", owner);
	eventManager->AddListener("Right", owner);
	eventManager->AddListener("Up", owner);
}

void Player::resetPlayer()
{
	//sets their health to max
	health = maxHealth;
	//stop the player moving in a direction
	left = false;
	right = false;
	((Physics*)owner->GetComponent(PHYSICS))->SetForces({ 0,0 });
	//move them back to the last checkpoint they moved over
	if (currentCheckpoint != nullptr) {
		Vector2f temp = ((Transform*)currentCheckpoint->GetComponent(TRANSFORM))->GetGlobalPos();
		((Transform*)owner->GetComponent(TRANSFORM))->SetPosition(((Transform*)currentCheckpoint->GetComponent(TRANSFORM))->GetGlobalPos() - ((Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM))->GetGlobalPos());
	}

}

void Player::EndLevel()
{
	// loads the next scene 
	SceneManager::GetInstance()->setScene(ObjectManager::GetInstance()->currentScene + 1);
}

void Player::Update()
{
	//move the player 
	Physics* physics = (Physics*)owner->GetComponent(PHYSICS);
	if(left)
		physics->SetXForce(-moveSpeed);
	else if(right)
		physics->SetXForce(moveSpeed);
	else
		physics->SetXForce(0);
	
	//check if the object is on a platform (they will have no downwards force if they are)
	onPlatform = (physics->GetForces().y == 0);

	//check for collisions that are not platforms (handled in physics)
	for (BaseObject* object : ((Physics*)owner->GetComponent(PHYSICS))->CheckForCollisions()) {
		if (object->HasTag("Enemy"))
			Damage(1);
	}

	//checks for overlaps
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
	//gets the eventKey and will set variables based on the inputs
	KeyInput* eventKey = (KeyInput*)event;
	string eventName = event->returnType();

	if (eventName == "Left")
		left = eventKey->GetKeyDown();
	else if (eventName == "Right")
		right = eventKey->GetKeyDown();
	else if (eventName == "Up"  && onPlatform) {
		//adds an inpuse to the current force to make them jump into the air
		((Physics*)owner->GetComponent(PHYSICS))->AddForce(Vector2f(0,-jumpForce));
		onPlatform = false;
	}
		
}

void Player::Damage(int value)
{
	//removes from health if too low then resets the player
	health -= value;
	if (health <= 0)
		resetPlayer();
}
