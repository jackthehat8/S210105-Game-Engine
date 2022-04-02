#pragma once
#include "BaseComponent.h"
#include "Vector.h"
#include <string>

using namespace std;

static enum PhysicsType {
    DYNAMIC,
    STATIC
};

static enum OverlapType {
    OVERLAP,
    COLLIDE
};

class Physics :
    public BaseComponent
{
public:
    Physics(BaseObject* owner_, PhysicsType physType_ = STATIC, OverlapType overlapType_ = COLLIDE);
    void UpdateColliderBounds();

    void Update();
    void DrawGui();

    vector <BaseObject*> CheckForOverlaps(string tag = "");
    vector <BaseObject*> CheckForCollisions(string tag = "");

    PhysicsType GetPhysType() { return physType; }    
    OverlapType GetOverlapType() { return overlapType; }

    Vector2f GetTopLeft() { return topLeft; }
    Vector2f GetTopRight() { return topRight; }
    Vector2f GetBottomLeft() { return bottomLeft; }
    Vector2f GetBottomRight() { return bottomRight; }
    Vector2f GetCentre() { return centre; }

    float GetLeft() { return left; }
    float GetRight() { return right; }
    float GetTop() { return top; }
    float GetBottom() { return bottom; }

    void SetLeft(float value);
    void SetRight(float value);
    void SetTop(float value);
    void SetBottom(float value);

    Vector2f GetForces() { return forces; }
    void SetForces(Vector2f forces_) { forces = forces_; }
    void SetXForce(float x) { forces.x = x; }
    void SetYForce(float y) {forces.y = y;}
    void AddForce(Vector2f newVector) { forces += newVector; }


private:
    PhysicsType physType;
    OverlapType overlapType;

    Vector2f topLeft;
    Vector2f topRight;
    Vector2f bottomLeft;
    Vector2f bottomRight;

    Vector2f centre;

    Vector2f forces = Vector2f(0,0);

    float left;
    float right;
    float top;
    float bottom;

    const float gravity = 75.0f;
    const int bufferDistance = 0;
};

