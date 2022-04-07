#pragma once
#include "BaseScript.h"
#include "Time.h"
class Enemy :
    public BaseScript
{
private:
    bool movingRight = true;

    int moveLength = 150;
    int moveSpeed = 1;

    float xStartPos;
    float xEndPos;

public:
    /// constructs an enemy
    /// sets the start positon equal to their current position
    /// calculates the end positon based on thier start pos + the moveLength
    /// gives the BaseObject the tag of enemy using BaseObject::AddTag()
    /// <param name="owner_"></param>
    Enemy(BaseObject* owner_);

    /// moves the enemy
    /// if the enemy passes either position it starts them moving in the opposite direction
    /// this makes it move between the 2 points
    void Update();
};

