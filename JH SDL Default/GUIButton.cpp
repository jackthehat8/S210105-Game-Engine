#include "GUIButton.h"
#include "EventManager.h"
#include "Sprite.h"
#include "ObjectManager.h"

GUIButton::GUIButton(BaseObject* owner_)
{
	owner = owner_;
	type = SCRIPT;
	EventManager::GetInstance()->AddListener("LMB", owner);
	UpdateColliderBounds();
}

void GUIButton::ButtonPressed()
{
}

bool GUIButton::CheckButtonPressed(Vector2f mousePos)
{
	if (!(left > mousePos.x || right < mousePos.x ||
		top > mousePos.y || bottom < mousePos.y))
		return true;
	return false;
}

void GUIButton::UpdateColliderBounds()
{
	Transform* transfrom = (Transform*)(owner->GetComponent(TRANSFORM));
	Sprite* sprite = (Sprite*)(owner->GetComponent(SPRITE));

	topLeft = transfrom->GetGlobalPos(); //position is from the top left

	left = topLeft.x;
	top = topLeft.y;
	float width = sprite->GetWidth();
	float height = sprite->GetHeight();
	bottom = topLeft.y + sprite->GetHeight();
	right = topLeft.x + sprite->GetWidth();

	topRight = Vector2f(right, top);
	bottomLeft = Vector2f(left, bottom);
	bottomRight = Vector2f(right, bottom);
}

void GUIButton::HandleEvent(BaseEvent* event)
{
	if (owner->GetCurrentScene() == ObjectManager::GetInstance()->currentScene) {
		if (event->returnType() == "LMB") {
			LMBInput* LMBevent = (LMBInput*)event;
			if (CheckButtonPressed(LMBevent->GetMousePos())) {
				ButtonPressed();
			}
		}
	}
}
