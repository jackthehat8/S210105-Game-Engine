#pragma once
#include "BaseScript.h"
#include "Events.h"
///This is used to make a button that can be press on screen
///
/// Any other button should inherit from this
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
    /// this will construct a button with bounds
    /// @note this will subscribe the BaseOject to listening for the left mouse button being pressed
    /// 
    /// <param name="owner_">this is the BaseObject that is the owner of the component</param>
    GUIButton(BaseObject* owner_);
    /// this is used to be called in an inherited item to run if the button has been pressed
    virtual void ButtonPressed();

    /// this checks if the button has been pressed 
    /// if it has it will call ButtonPressed();
    /// <param name="mousePos">the position the mouse clicked on the screen</param>
    bool CheckButtonPressed(Vector2f mousePos);

    /// updates the bounds of the button to make sure it is accuarte as it could have move
    void UpdateColliderBounds();

    /// is called by the EventManager when the mouse is cliced to check if the button has been pressed
    /// <param name="event"></param>
    void HandleEvent(BaseEvent* event);
};

