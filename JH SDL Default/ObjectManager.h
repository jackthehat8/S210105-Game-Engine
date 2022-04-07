#pragma once
#include "SDL.h"
#include <vector>
#include <string>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>
using namespace std;

/// <summary>
/// This stores a name for each component type that is possible to be added to BaseObject
/// 
/// This is used when trying to access a component on an object
/// </summary>
static enum ComponentType {
	TRANSFORM,
	SPRITE,
	TEXT,
	PHYSICS,
	COMPONENT_COUNT,
	SCRIPT //multiple can be added so has its own vector instead of being in the component array
};

class BaseComponent;
class BaseObject;

class ObjectManager
{
public:
	/// Nothing is constructed
	ObjectManager();
	/// Nothing needs to be destroyed other then the obeject itself so this does nothing
	~ObjectManager();

	/// <summary>
	/// Gets the instance of the ObjectManager
	/// 
	/// It is a singleton so allows the only instance
	/// </summary>
	static ObjectManager* GetInstance();

	/// Used to call PreRender in BaseObject in Update
	virtual void PreRender();
	/// Used to call Render in BaseObject in Update
	virtual void Render();
	/// Used to call PostRender in BaseObject in Update
	virtual void PostRender();

	/// Used to call CheckIfClicked in BaseObject in Update
	virtual bool CheckIfClicked();
	/// Used to call DrawGui in BaseObject in Update
	virtual void DrawGui();

	/// Used to call OnMouseDown in BaseObject in Update
	virtual void OnMouseDown();
	/// Used to call OnMouseHeld in BaseObject in Update
	virtual void OnMouseHeld();
	/// Used to call OnMouseUp in BaseObject in Update
	virtual void OnMouseUp();

	/// Sets the selceted object to be used for the inspector and Hierarchy
	void SetSelectedObject(BaseObject* object);

	/// Gets the selected object
	/// 
	/// This is mostly useful for the inspector and hierarchy
	BaseObject* GetSelectedObject() { return selectedObject; }

	/// Sets the held object for dragging an item when tools are set active
	void SetHeldObject(BaseObject* object);

	/// sorts the BaseObjects based on their render layer
	/// the lower the number, the further back in the scene it is rendered
	void sortObjects();

	/// The Quick Sort used in sortObjects
	/// This is called recursivly to sort the entire list
	/// <param name="input">a vector of objects to be sorted</param>
	/// <param name="first">the first item in the list</param>
	/// <param name="last">the last item in the list</param>
	/// <returns>a sorted list</returns>
	std::vector<BaseObject*> QuickSort(std::vector<BaseObject*> input, int first, int last);

	/// This calls PreRender, Render and PostRender for the current scene's objects
	/// 
	/// This also calls drawGui on the selectedObject to complete the inspector
	/// It also moves the object bases on mouse position if it is being held
	void Update();

	/// <summary>
	/// Gets the objects currently being displayed on screen and returns them
	/// </summary>
	/// <returns>a vector of BaseObjects</returns>
	vector<BaseObject*> GetObjects() { return objects; }
	
	/// <summary>
	/// Adds an object to the currently rendering objects
	/// </summary>
	/// <param name="object">object to be added</param>
	void AddObject(BaseObject* object);

	/// <summary>
	/// Gets the list of scene roots for the game
	/// </summary>
	/// <returns>a vector of scene roots</returns>
	vector<BaseObject*> GetSceneRoots() { return sceneRoots; }

	/// <summary>
	/// Converts the components name into a const char*
	/// </summary>
	/// <param name="type"> the Component type to be made into a string</param>
	/// <returns>the name of the component type</returns>
	const char* ComponentTypeToString(ComponentType type);
	
	/// <summary>
	/// Gives the objects to be updated and drawn in the new scene
	/// 
	/// This also sets currentScene to the number of the current scene
	/// </summary>
	/// <param name="newScene">a vector of BaseObjects* to be set as the new scene</param>
	/// <param name="sceneNumber">the new scene number</param>
	void SetScene(vector<BaseObject*> newScene, int sceneNumber) { objects = newScene; currentScene = sceneNumber; }

	/// creates a new scene root for new scene
	void AddSceneRoot();

	/// The storage of the current scene
	int currentScene = 0;
private:
	/// the instance of ObjectManager
	static ObjectManager* instance;

	/// the storage of scene roots
	vector<BaseObject*> sceneRoots;

	/// the storage of the selected object
	BaseObject* selectedObject;
	
	/// the storage of the held object
	BaseObject* heldObject;

	/// the storage of the objects currently being drawn
	std::vector<BaseObject*> objects;
};



