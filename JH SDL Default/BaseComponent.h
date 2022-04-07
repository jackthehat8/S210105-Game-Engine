#pragma once
#include "BaseObject.h"

#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>
class BaseComponent
{
public:
	/// used to call Update in components
	virtual void Update() {};
	///used to call DrawGui in components
	virtual void DrawGui() {};

	/// used to call HandleEvent in components
	virtual void HandleEvent(BaseEvent* event) {};

	/// gets the BaseObject that owns the component
	BaseObject* GetOwner() { return owner; }
	/// used to get the type of the component
	ComponentType GetType() { return type; }

protected:
	BaseObject* owner;
	ComponentType type;
};

