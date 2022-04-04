#pragma once
#include "BaseScript.h"
#include "Events.h"
class GUIButton :
    public BaseScript
{
private:
    BaseObject* owner;

    Vector2f topLeft;
    Vector2f topRight;
    Vector2f bottomLeft;
    Vector2f bottomRight;

    float left;
    float right;
    float top;
    float bottom;
public:
    GUIButton(BaseObject* owner_);
    virtual void ButtonPressed();
    bool CheckButtonPressed(Vector2f mousePos);
    void UpdateColliderBounds();
    void HandleEvent(BaseEvent* event);
};

