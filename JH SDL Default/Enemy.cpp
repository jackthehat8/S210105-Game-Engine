#include "Enemy.h"

Enemy::Enemy(BaseObject* owner_)
{
	// set default values
	owner = owner_;
	owner->AddTag("Enemy");
	xStartPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos().x;
	//adds the moveLenght to start pos to get an end pos
	xEndPos = xStartPos + moveLength;
}

void Enemy::Update()
{
	//get reference to the objects transform
	Transform* transfrom = (Transform*)owner->GetComponent(TRANSFORM);
	float currentXPos = transfrom->GetGlobalPos().x;
	// gets the root offset to that the positions to move to are offset
	float xSceneRootOffset = ((Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM))->GetGlobalPos().x;
	//swtich from moving left to moving right
	if (currentXPos <= xStartPos + xSceneRootOffset)
		movingRight = true;
	//switch from moving right to moving left
	else if (xEndPos + xSceneRootOffset <= currentXPos)
		movingRight = false;

	//move the enemy
	Physics* physics = (Physics*)owner->GetComponent(PHYSICS);
	if (movingRight)
		physics->SetXForce(moveSpeed);
	else
		physics->SetXForce(-moveSpeed);
}
