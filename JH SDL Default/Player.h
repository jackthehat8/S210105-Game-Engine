#pragma once
#include "BaseScript.h"
class Player :
    public BaseScript
{
private:
    int health;
    int maxHealth;

    int moveSpeed;
    int jumpMultiplier;

    void jump();

    void resetPlayer();

    bool landed = false;

    Vector2f respawnPosition;
public:
    Player(BaseObject* owner_);

    void update();
};

