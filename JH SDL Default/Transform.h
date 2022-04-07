#pragma once
#include "BaseComponent.h"
#include "BaseObject.h"
#include "Vector.h"
class Transform : 
    public BaseComponent
{
public:
    /// This sets the positon and owner of the BaseObject
    /// <param name="x"> the x position</param>
    /// <param name="y"> the y position </param>
    /// <param name="owner_"> the BaseObject that the component is on</param>
    /// Example
    /// ~~~~~.cpp
    /// BaseObject* tempObject = new BaseObject("temp", 550, 275, 0);
    /// tempObject->AddComponent(new Text("assets/temp.ttf", 100, tempObject, "this is a temporary message", { 0,0,0 }, { 125,50 }));
    /// ~~~~~
    Transform(int x, int y, BaseObject* owner_) { Transform(Vector2f(x, y), owner_); }

    /// This sets the positon and owner of the BaseObject
    /// <param name="pos">the position of the BaseObject</param>
    /// <param name="owner_"> the BaseObject that the component is on</param>
    Transform(Vector2f pos, BaseObject* owner_);

    /// This draws the position informaion of a BaseObject to the inspector window
    void DrawGui();

    /// Adds together the BaseObject's local position and thier parents (all the way to the scene root) together to get its positon on the screen
    /// <returns>the sum of its parents positon</returns>
    Vector2f GetGlobalPos();

    /// <returns>the BaseObject's local position</returns>
    Vector2f GetLocalPosition() { return position; }

    /// sets the positon of the object
    /// <param name="x_">x positon to move to</param>
    /// <param name="y_">y position to move to</param>
    void SetPosition(int x_, int y_);
    /// sets the y positon of the object
    /// <param name="y_">y position to move to</param>
    void SetYPosition(int y_) { position.y = y_; }
    /// sets the x positon of the object
    /// <param name="x_">x position to move to</param>
    void SetXPosition(int x_) { position.x = x_; }
    /// sets the positon of the object
    /// <param name="newPos">the positon to move to</param>
    void SetPosition(Vector2f newPos);
protected:
    /// stores the local positon of the BaseObeject
    Vector2f position;
    
};

