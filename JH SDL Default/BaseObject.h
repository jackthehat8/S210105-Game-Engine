#pragma once
#include "ObjectManager.h"
#include "Events.h"
#include <map>

class Transform;

using namespace std;
class BaseObject :
    public ObjectManager
{
public:
    BaseObject(const char* name_, int x = 0, int y = 0);

    void PreRender();
    void Render();
    void PostRender();

    void DrawGui();
    void DrawHierarchy(ImGuiTreeNodeFlags flags);

    const char* GetName() { return name; }

    void SetParent(BaseObject* parent_);
    void RemoveParent();
    BaseObject* GetParent() { return parent; }

    void OnMouseHeld();

    vector<string> GetTags() { return tags; }
    void AddTag(string tag);
    void RemoveTag(string tag);
    bool HasTag(string tag);

    void AddComponent(BaseComponent* component);
    BaseComponent* GetComponent(ComponentType);
   
    void HandleEvent(BaseEvent* event);

protected:
    vector<BaseComponent*> scripts;
    BaseComponent* components[COMPONENT_COUNT]; //does not include scripts

    BaseObject* parent;

    vector<BaseObject*> children;

    vector<string> tags;

    char* name;
    void AddChild(BaseObject* child) { children.push_back(child); }
    void RemoveChild(BaseObject*);

    void AddScript(BaseComponent* script) { scripts.push_back(script); }

};

