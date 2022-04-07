#pragma once
#include "ObjectManager.h"
#include "Events.h"
#include <map>

class Transform;

using namespace std;

/// <summary>
/// The main object that components can be attached to
/// 
/// The position is based off the top left point of any component added
/// </summary>
class BaseObject :
    public ObjectManager
{
public:
    /// <summary>
    /// This constructs a base object
    /// 
    /// It will add itself to the scene specified and set its parent to the Scene Root
    /// </summary>
    /// <param name="name_">This is the name of the base object</param>
    /// <param name="x">The x position of the Top Left of the BaseObject</param>
    /// <param name="y">The y position of the Top Left of the BaseObject</param>
    /// <param name="sceneNumber">The scene that the BaseObject will be drawn into</param>
    BaseObject(const char* name_, int x = 0, int y = 0, int sceneNumber = 0);

    /// This is called before the object has been rendered
    /// 
    /// This calls all Script components that are added to the object and the Physics component
    void PreRender();

    /// This renders the object
    /// 
    /// This calls update on a Sprite component and a Text component
    void Render();

    /// This is called after the object has been rendered
    void PostRender();

    /// This is used to draw the Inspector if the object has been selected
    void DrawGui();

    /// This is used to draw the object and its children to the Hierarchy tool
    /// 
    /// This will recursivly call its children to create a hierarchy
    /// <param name="flags">this will take any flags needed for the hierarchy</param>
    void DrawHierarchy(ImGuiTreeNodeFlags flags);

    /// <returns>returns the name of the object</returns>
    const char* GetName() { return name; }

    /// sets the parent of the object
    /// <param name="parent_"> The object that is to be set as the parent</param>
    void SetParent(BaseObject* parent_);

    /// removes the current parent, setting it to the scene root
    void RemoveParent();

    /// gets the current parent of the object
    BaseObject* GetParent() { return parent; }

    /// Used when the tools are turned on to allow the user to move items around based on their mouse
    void OnMouseHeld();

    /// Returns the tags of the object
    /// <returns> This is a vector of strings that can be searched through</returns>
    vector<string> GetTags() { return tags; }

    /// Adds a new tag to the object
    /// 
    /// If the tag already exists then it will not be added
    /// <param name="tag">The name of the tag to be added</param>
    void AddTag(string tag);

    /// Removes the tag from the object if found
    /// <param name="tag">The name of the tag to be removed</param>
    void RemoveTag(string tag);

    /// Will check if the tag is on the game object
    /// <param name="tag">The name of the tag check if it has</param>
    /// <returns>Returns true or false if the object has the tag</returns>
    bool HasTag(string tag);

    /// <summary>
    /// Addes a component to the obejct
    /// 
    /// Only one of each type of compoenent can be added to the object, except for scripts
    /// The components are Sprite, Transform, Physics, Text and BaseScript
    /// </summary>
    /// <param name="component">A component that inherits from BaseComponent can be given</param>
    void AddComponent(BaseComponent* component);

    /// <summary>
    /// Gets the component from the object if it has it
    /// 
    /// If there is not one then it will return nullpointer
    /// </summary>
    /// <param name="">A name from the enum ComponentType</param>
    /// <returns>Returns the BaseComponent unless it does not exist where a nullpointer will be returned/returns>
    BaseComponent* GetComponent(ComponentType);
   
    /// This is called by the EventManager if a event the object is listening for is called
    /// 
    /// This calls the same event in components to allow them to handle events if needed
    /// <param name="event">The event input in FireEvents</param>
    void HandleEvent(BaseEvent* event);
   
    /// <returns>The scene the object is placed in</returns>
    int GetCurrentScene() { return scene; }

protected:
    /// stores the scripts
    vector<BaseComponent*> scripts;

    /// stores the components of the object
    BaseComponent* components[COMPONENT_COUNT]; //does not include scripts

    /// stores the parent of the object
    BaseObject* parent;

    /// stores the children of the object
    vector<BaseObject*> children;

    /// stores the tags of the object
    vector<string> tags;

    /// The scene the object is in
    int scene;

    /// The name of the object
    char* name;

    /// Used to add a child to an object
    /// 
    /// It is called in SetParent so does not need to be accessed outside of the object itself
    void AddChild(BaseObject* child) { children.push_back(child); }

    /// Used to remove a child from the object
    /// 
    /// Called in RemoveParent so does not need to be accessed outside of the object itself
    void RemoveChild(BaseObject*);

    /// Used to add a script to the list of scripts
    /// 
    /// Is called in AddComponent so does not need to be accessed outside of the object itself
    void AddScript(BaseComponent* script) { scripts.push_back(script); }

};

