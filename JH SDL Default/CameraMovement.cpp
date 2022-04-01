#include "CameraMovement.h"
#include "Transform.h"

CameraMovement::CameraMovement(BaseObject* owner_, bool changeX_, bool changeY_)
{
	owner = owner_;
	changeX = changeX_;
	changeY = changeY_;
	previousFramePos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();
}

void CameraMovement::Update()
{
	Vector2f currentPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();

	float xChange = 0;
	float yChange = 0;

	if(changeX)
		xChange = currentPos.x - previousFramePos.x;
	if(changeY)
		yChange = currentPos.y - previousFramePos.y;

	Transform* sceneRootTransform = (Transform*)ObjectManager::GetInstance()->GetSceneRoot()->GetComponent(TRANSFORM);
	sceneRootTransform->SetPosition(sceneRootTransform->GetGlobalPos().x - xChange, sceneRootTransform->GetGlobalPos().y - yChange);

	previousFramePos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();
}

void CameraMovement::HandleEvent(BaseEvent* event)
{
}
