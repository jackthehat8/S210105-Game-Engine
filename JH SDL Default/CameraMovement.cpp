#include "CameraMovement.h"
#include "Transform.h"
#include "Constants.h"

CameraMovement::CameraMovement(BaseObject* owner_, bool changeX_, bool changeY_)
{
	owner = owner_;
	changeX = changeX_;
	changeY = changeY_;

	Vector2f scrrenStartPos = Vector2f(ScreenWidth / 2, ScreenHeight / 2);
	Vector2f currentPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();

	float xChange = 0;
	float yChange = 0;
	if (changeX)
		xChange = (currentPos.x - scrrenStartPos.x)/2;
	if (changeY)
		yChange = currentPos.y - scrrenStartPos.y;

	Transform* sceneRootTransform = (Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM);
	sceneRootTransform->SetPosition(sceneRootTransform->GetGlobalPos().x - xChange, sceneRootTransform->GetGlobalPos().y - yChange);

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

	Transform* sceneRootTransform = (Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM);
	sceneRootTransform->SetPosition(sceneRootTransform->GetGlobalPos().x - xChange, sceneRootTransform->GetGlobalPos().y - yChange);

	previousFramePos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();
}

void CameraMovement::HandleEvent(BaseEvent* event)
{
}
