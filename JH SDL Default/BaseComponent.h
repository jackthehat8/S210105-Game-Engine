#pragma once
#include "BaseObject.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>
class BaseComponent
{
public:
	virtual void Update();
	virtual void DrawGui();

	virtual void HandleEvent(BaseEvent* event);

	BaseObject* GetOwner() { return owner; }
	ComponentType GetType() { return type; }

protected:
	BaseObject* owner;
	ComponentType type;
};

