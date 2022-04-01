#pragma once
#include "BaseScript.h"
class CameraMovement :
    public BaseScript
{

private:
    Vector2f previousFramePos;

    bool changeX;
    bool changeY;
public:

    /// <summary>
    /// </summary>
    /// <param name="owner_"></param>
    /// <param name="changeX_">allow x movement</param>
    /// <param name="changeY_">alows y movement</param>
    CameraMovement(BaseObject* owner_, bool changeX_, bool changeY_);
   
    void Update();
    void HandleEvent(BaseEvent* event);
};

