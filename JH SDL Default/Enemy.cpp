#include "Enemy.h"

Enemy::Enemy(BaseObject* owner_)
{
	owner = owner_;
	owner->AddTag("Enemy");
	xStartPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos().x;
	xEndPos = xStartPos + moveLength;
}

void Enemy::Update()
{
	Transform* transfrom = (Transform*)owner->GetComponent(TRANSFORM);
	float currentXPos = transfrom->GetGlobalPos().x;
	float xSceneRootOffset = ((Transform*)ObjectManager::GetInstance()->GetSceneRoot()->GetComponent(TRANSFORM))->GetGlobalPos().x;
	if (currentXPos <= xStartPos + xSceneRootOffset)
		movingRight = true;
	else if (xEndPos + xSceneRootOffset <= currentXPos)
		movingRight = false;

	Physics* physics = (Physics*)owner->GetComponent(PHYSICS);
	if (movingRight)
		physics->SetXForce(moveSpeed);
	else
		physics->SetXForce(-moveSpeed);
}
