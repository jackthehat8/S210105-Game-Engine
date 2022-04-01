#pragma once
#include "BaseScript.h"

class Player :
    public BaseScript
{
private:
    int health;
    int maxHealth;

    float moveSpeed = 1.0f;
    float jumpForce = 5.0f;

    void jump();

    void resetPlayer();

    bool landed = false;

    BaseObject* currentCheckpoint;
public:
    Player(BaseObject* owner_);

    void update();

    void HandleEvent(BaseEvent* event);
};

