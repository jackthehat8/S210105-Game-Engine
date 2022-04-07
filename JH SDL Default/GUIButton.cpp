#include "GUIButton.h"
#include "EventManager.h"
#include "Sprite.h"
#include "ObjectManager.h"

GUIButton::GUIButton(BaseObject* owner_)
{
	//stores values
	owner = owner_;
	type = SCRIPT;
	//adds object to listener for Left Mouse Button presses
	EventManager::GetInstance()->AddListener("LMB", owner);
	UpdateColliderBounds();
}

void GUIButton::ButtonPressed()
{
}

bool GUIButton::CheckButtonPressed(Vector2f mousePos)
{
	//based on the bounds of the collider it will return if the position is within the bounds of the box
	UpdateColliderBounds();
	if (!(left > mousePos.x || right < mousePos.x ||
		top > mousePos.y || bottom < mousePos.y))
		return true;
	return false;
}

void GUIButton::UpdateColliderBounds()
{
	//gets the transform for position and sprite for sprite bounds
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));

	topLeft = transfrom->GetGlobalPos(); //position is from the top left

	//sets the extents of the box
	left = topLeft.x;
	top = topLeft.y;
	float width = sprite->GetWidth();
	float height = sprite->GetHeight();
	bottom = topLeft.y + sprite->GetHeight();
	right = topLeft.x + sprite->GetWidth();

	//sets corners based on it
	topRight = Vector2f(right, top);
	bottomLeft = Vector2f(left, bottom);
	bottomRight = Vector2f(right, bottom);
}

void GUIButton::HandleEvent(BaseEvent* event)
{
	//calls button pressed if the mouse click was within the bounds of the box
	if (owner->GetCurrentScene() == ObjectManager::GetInstance()->currentScene) {
		if (event->returnType() == "LMB") {
			LMBInput* LMBevent = (LMBInput*)event;
			if (CheckButtonPressed(LMBevent->GetMousePos())) {
				ButtonPressed();
			}
		}
	}
}
