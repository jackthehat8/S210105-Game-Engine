#pragma once
#include "BaseComponent.h"
#include "Vector.h"
#include <string>

using namespace std;

///this is used to generate a physics type 
///
/// there are 2 types of physics; Static and Dynamic
/// Static will make the item not move using physics but it can still be overlapped/collided with
/// Dynamic will give it gravity and allow it move freely move using the physics forces
/// @see Physics
static enum PhysicsType {
    DYNAMIC,
    STATIC
};

/// this is used to generate an overlap type
/// 
/// there are 2 types of overlap; Overlap and Collision
/// Overlap is used for CheckForOverlaps() and will not collide with collision items
/// Collision is used for CheckForCollisions() and a BaseObject with the tag "platform" will automatically be collided with and not let the 2 BaseObjects overlap
/// @see Physics
static enum OverlapType {
    OVERLAP,
    COLLIDE
};

class Physics :
    public BaseComponent
{
public:
    /// This genrates a physics box collider 
    /// <param name="owner_">the BaseObject that the component is to be added onto</param>
    /// <param name="physType_"> the PhysicsType for the object</param>
    /// <param name="overlapType_">the OverlapType for the object</param>
    /// Example
    /// ~~~~~.cpp
    /// BaseObject* tempObject = new BaseObject("temp", 550, 275, 0);
    /// tempObject->AddComponent(new Physics(tempObject, DYNAMIC, COLLIDE));
    /// ~~~~~
    /// @see PhysicsType and OverlapType
    Physics(BaseObject* owner_, PhysicsType physType_ = STATIC, OverlapType overlapType_ = COLLIDE);

    /// Will calculate the corners of the box collider
    /// 
    /// this also makes floats for the extents of the collider (left,right,top and bottom)
    void UpdateColliderBounds();

    /// This will move the BaseObject based on forces and check for platform collisions
    /// If the BaseObject has an PhysicsType of Dynamic
    ///     Gravity will be applied to it and it will be moved before collisions occur
    /// @note if PhysicsType is Static this step is not completed
    /// 
    /// If the CollisionType is Collide
    ///     CheckForColiisions() is ran to see if it is overlapping another collision object
    ///     if it is then it is moved out of the collision
    ///     this is done by setting the side(s) that is/are overlapping the other object and setting equal to the opposite side of the overlap
    ///     ### Example
    /// ~~~~.cpp
    ///     box1.SetLeft(box2.GetRight()) //this would set the left of box1 to the x value of box y
    /// ~~~~
    void Update();

    ///  This displays the forces, PhysicsType and OverlapType in the inspector
    void DrawGui();

    /// checks for overlaps with BaseObjects with the Overlap CollisionType
    /// <param name="tag">a tag can be used to be specific to a group of BaseObjects
    /// @note if this is left blank it will get all overlapping BaseOjects</param>
    /// 
    /// <returns>a vector of BaseObjects that are overlapping</returns>
    vector <BaseObject*> CheckForOverlaps(string tag = "");

    /// checks for collisons with BaseObjects with the Collide CollisionType
    /// <param name="tag">a tag can be used to be specific to a group of BaseObjects
    /// @note if this is left blank it will get all overlapping BaseOjects</param>
    /// 
    /// <returns>a vector of BaseObjects that are colliding</returns>
    vector <BaseObject*> CheckForCollisions(string tag = "");

    /// <returns>the physics type of the BaseObject</returns>
    PhysicsType GetPhysType() { return physType; }    

    /// <returns>the overlap type of the BaseObject</returns>
    OverlapType GetOverlapType() { return overlapType; }

    /// <returns>the posititon of the top left corner</returns>
    Vector2f GetTopLeft() { return topLeft; }
    /// <returns>the posititon of the top right corner</returns>
    Vector2f GetTopRight() { return topRight; }
    /// <returns>the posititon of the bottom left corner</returns>
    Vector2f GetBottomLeft() { return bottomLeft; }
    /// <returns>the posititon of the bottom right corner</returns>
    Vector2f GetBottomRight() { return bottomRight; }
    /// <returns>the posititon of the centre</returns>
    Vector2f GetCentre() { return centre; }

    /// <returns>the x posititon on the left of the BaseObject</returns>
    float GetLeft() { return left; }
    /// <returns>the x posititon on the right of the BaseObject</returns>
    float GetRight() { return right; }
    /// <returns>the y posititon on the top of the BaseObject</returns>
    float GetTop() { return top; }
    /// <returns>the y posititon on the bottom of the BaseObject</returns>
    float GetBottom() { return bottom; }

    /// sets the left x position to a value
    void SetLeft(float value);
    /// sets the right x position to a value
    void SetRight(float value);
    /// sets the top y position to a value
    void SetTop(float value);
    /// sets the bottom y position to a value
    void SetBottom(float value);

    /// <returns>the current forces acting on the BaseObject</returns>
    Vector2f GetForces() { return forces; }
    /// <param name="forces_">the new x and y forces</param>
    void SetForces(Vector2f forces_) { forces = forces_; }
    /// <param name="x">the new x force to be set</param>
    void SetXForce(float x) { forces.x = x; }
    /// <param name="y">he new y force to be set</param>
    void SetYForce(float y) {forces.y = y;}
    /// Adds the force to the current forces
    /// <param name="newVector">the amount to add onto the curent forces</param>
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

