#include "Player.h"
#include "Events.h"
#include "Physics.h"
#include "Transform.h"

void Player::resetPlayer()
{
	health = maxHealth;
	((Transform*)owner->GetComponent(TRANSFORM))->SetPosition(respawnPosition);

}

Player::Player(BaseObject* owner_)
{
	owner = owner_;
	respawnPosition = ((Transform*)owner->GetComponent(TRANSFORM))->GetLocalPosition();
}

void Player::update()
{

}
