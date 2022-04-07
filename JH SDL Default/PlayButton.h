#pragma once
#include "GUIButton.h"
class PlayButton :
    public GUIButton
{
public:
    /// calls the GUIButton constructor
    PlayButton(BaseObject* owner_) : GUIButton(owner_) {}

    /// loads the first level throught the SceneManager
    void ButtonPressed();
};

