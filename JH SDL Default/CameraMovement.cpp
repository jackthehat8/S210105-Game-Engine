#include "CameraMovement.h"
#include "Transform.h"
#include "Window Constants.h"

CameraMovement::CameraMovement(BaseObject* owner_, bool changeX_, bool changeY_)
{
	//sets the values passed in to their corresponding variable
	owner = owner_;
	changeX = changeX_;
	changeY = changeY_;

	//sets the start pos equal to the default start of the screen
	Vector2f scrrenStartPos = Vector2f(ScreenWidth / 2, ScreenHeight / 2);
	//gets the current position the camera is at
	Vector2f currentPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();

	float xChange = 0;
	float yChange = 0;
	if (changeX)// move the camera in x
		xChange = (currentPos.x - scrrenStartPos.x)/2;
	if (changeY)//move the camera in y
		yChange = currentPos.y - scrrenStartPos.y;
	
	//gets the transform of the scene root and moves it opposite to the movement of the camera (camera moves right, scene moves left)
	Transform* sceneRootTransform = (Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM);
	sceneRootTransform->SetPosition(sceneRootTransform->GetGlobalPos().x - xChange, sceneRootTransform->GetGlobalPos().y - yChange);

	//sets the current position 
	previousFramePos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();
}

void CameraMovement::Update()
{
	/// get the current position
	Vector2f currentPos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();

	float xChange = 0;
	float yChange = 0;

	// calculate the position change compared to the previous frame
	if(changeX)
		xChange = currentPos.x - previousFramePos.x;
	if(changeY)
		yChange = currentPos.y - previousFramePos.y;

	// move the scene root based on the chagne
	Transform* sceneRootTransform = (Transform*)ObjectManager::GetInstance()->GetSceneRoots()[owner->GetCurrentScene()]->GetComponent(TRANSFORM);
	sceneRootTransform->SetPosition(sceneRootTransform->GetGlobalPos().x - xChange, sceneRootTransform->GetGlobalPos().y - yChange);

	//store the current position to be used next frame
	previousFramePos = ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos();
}