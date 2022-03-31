#pragma once
#include "BaseComponent.h"
#include "BaseObject.h"
#include "Vector.h"
class Transform : 
    public BaseComponent
{
public:

    Transform(int x, int y, BaseObject* owner_) { Transform(Vector2f(x, y), owner_); }
    Transform(Vector2f pos, BaseObject* owner_);

    void Update();

    void DrawGui();

    Vector2f GetGlobalPos();

    Vector2f GetLocalPosition() { return position; }

    void SetPosition(int x_, int y_);
    void SetYPosition(int y_) { position.y = y_; }
    void SetXPosition(int x_) { position.x = x_; }
    void SetPosition(Vector2f newPos);
protected:
    Vector2f position;
    
};

