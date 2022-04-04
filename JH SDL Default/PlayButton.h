#pragma once
#include "GUIButton.h"
class PlayButton :
    public GUIButton
{
public:
    PlayButton(BaseObject* owner_) : GUIButton(owner_) {}
    void ButtonPressed();
};

