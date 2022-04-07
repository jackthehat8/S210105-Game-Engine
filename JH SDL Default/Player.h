#pragma once
#include "BaseScript.h"

class Player :
    public BaseScript
{
private:
    int health;
    int maxHealth = 1;

    float moveSpeed = 15.0f;
    float jumpForce = 25.0f;

    bool left;
    bool right;

    /// moves the player to the previous checkpoint
    void resetPlayer();

    bool onPlatform = false;

    BaseObject* currentCheckpoint;

    bool hasKey = false;

    /// loads the win screen
    void EndLevel();
public:
    /// constructs the player script and assigns it to the BaseObject
    /// it also sets the BaseObject as listeners for left, right and up for movement
    Player(BaseObject* owner_);

    /// moves the player based on inputs
    /// checks if the player is colliding an enemy
    /// checks if the player is overlapping a key, the door or a checkpoint
    void Update();

    /// Gets the Events from the EventManager and sets variables accordingly
    void HandleEvent(BaseEvent* event);

    /// damages the player based on the input value
    /// if health is 0 then the player is reset
    /// <param name="value">damage amount</param>
    void Damage(int value);
};

