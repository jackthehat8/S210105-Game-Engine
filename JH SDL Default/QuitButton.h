#pragma once
#include "GUIButton.h"
class QuitButton :
    public GUIButton
{
public:
    /// calls the GUIButton constructor
    QuitButton(BaseObject* owner_) : GUIButton(owner_) {}

    /// Queues a QuitEvent in the EventManage
    void ButtonPressed();
};

