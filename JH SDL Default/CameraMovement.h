#pragma once
#include "BaseScript.h"
/// <summary>
/// moves the sceneRoot based on the movement of the camera 
/// 
/// when the camera's positon changes it moves the scene root by the same amount in the opposide direction
/// </summary>
class CameraMovement :
    public BaseScript
{

private:
    Vector2f previousFramePos;

    bool changeX;
    bool changeY;
public:

    /// <param name="owner_"></param>
    /// <param name="changeX_">allow x movement (if set to false it will not move in x)</param>
    /// <param name="changeY_">alows y movement (if set to false it will not move in y)</param>
    CameraMovement(BaseObject* owner_, bool changeX_, bool changeY_);
   
    /// compares the previous frame's positon to the current positon and will move the scene root based on the change between frames
    void Update();
};

