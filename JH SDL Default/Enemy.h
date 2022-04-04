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

    Enemy(BaseObject* owner_);

    void Update();
};

