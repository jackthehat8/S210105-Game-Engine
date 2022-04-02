#pragma once
#include "BaseScript.h"

class Player :
    public BaseScript
{
private:
    int health;
    int maxHealth;

    float moveSpeed = 15.0f;
    float jumpForce = 25.0f;

    bool left;
    bool right;

    void jump();

    void resetPlayer();

    bool onPlatform = false;

    BaseObject* currentCheckpoint;
public:
    Player(BaseObject* owner_);

    void Update();

    void HandleEvent(BaseEvent* event);
};

