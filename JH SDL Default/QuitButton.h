#pragma once
#include "GUIButton.h"
class QuitButton :
    public GUIButton
{
public:
    QuitButton(BaseObject* owner_) : GUIButton(owner_) {}
    void ButtonPressed();
};

