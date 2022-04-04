#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>

using namespace std;
static enum ComponentType {
	TRANSFORM,
	SPRITE,
	AUDIO,
	TEXT,
	PHYSICS,
	COMPONENT_COUNT,
	SCRIPT //multiple can be added so has its own vector instead of being in the component array
};

//struct Component {
//	void* data;
//	ComponentType type;
//
//	Component(void* data_, ComponentType type_) {
//		data = data_;
//		type = type_;
//	}
//};

class BaseComponent;
class BaseObject;

class ObjectManager
{
public:

	ObjectManager();
	~ObjectManager();
	static ObjectManager* GetInstance();

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();

	virtual bool CheckIfClicked();
	virtual void DrawGui();

	virtual void OnMouseDown();
	virtual void OnMouseHeld();
	virtual void OnMouseUp();

	void SetSelectedObject(BaseObject* object);
	void SetHeldObject(BaseObject* object);

	void sortObjects();
	std::vector<BaseObject*> QuickSort(std::vector<BaseObject*> input, int first, int last);

	void Update();

	vector<BaseObject*> GetObjects() { return objects; }
	
	void AddObject(BaseObject* object);
	void AddRenderer(SDL_Renderer* renderer);

	vector<BaseObject*> GetSceneRoots() { return sceneRoots; }

	const char* ComponentTypeToString(ComponentType type);
	
	void SetScene(vector<BaseObject*> newScene, int sceneNumber) { objects = newScene; currentScene = sceneNumber; }

	void AddSceneRoot();

	int currentScene = 0;
private:
	static ObjectManager* instance;

	vector<BaseObject*> sceneRoots;

	BaseObject* selectedObject;
	
	BaseObject* heldObject;

	std::vector<BaseObject*> objects;
	SDL_Renderer* m_renderer;

};



