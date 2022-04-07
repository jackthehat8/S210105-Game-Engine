#include "BaseObject.h"
#include <iostream>
#include "Transform.h"
#include "BaseComponent.h"
#include "BaseScript.h"
#include "SceneManager.h"

BaseObject::BaseObject(const char* name_, int x, int y, int sceneNumber)
{
	//generates a transform and adds it as a component
	AddComponent(new Transform(Vector2f(x, y), this));
	scene = sceneNumber;
	//checks the item isnt the scene root as it shouldnt run the following code if it is
	if (name_ != "Scene Root") {
		SceneManager::GetInstance()->addObjectToScene(this, sceneNumber);
		SetParent(ObjectManager::GetInstance()->GetSceneRoots()[scene]);
	}
	name = (char*)name_;
}

void BaseObject::OnMouseHeld()
{
	//sets the position
	//if no parnet it will set the local position
	Transform* transform = (Transform*)components[TRANSFORM];
	if (parent == nullptr)
		transform->SetPosition(Vector2f(transform->GetLocalPosition().x + ImGui::GetIO().MouseDelta.x, 
			transform->GetLocalPosition().y + ImGui::GetIO().MouseDelta.y));
	//if parent it removes the global position of the parent
	else {
		Vector2f globalPos = transform->GetGlobalPos();
		globalPos.x += ImGui::GetIO().MouseDelta.x;
		globalPos.y += ImGui::GetIO().MouseDelta.y;

		transform->SetPosition(globalPos - ((Transform*)(parent->GetComponent(TRANSFORM)))->GetGlobalPos());
	}
}

void BaseObject::AddTag(string tag)
{
	//checks if the tag is already added to the object
	bool exists = false;
	for (string currentTag : tags)
	{
		if (tag == currentTag) {
			exists = true;
			break;
		}
	}

	//adds the tag if it hasnt been added
	if (!exists)
		tags.push_back(tag);
}

void BaseObject::RemoveTag(string tag)
{
	//removes the tag if it is on the object
	for (int i = 0; i < tags.size(); i++)
	{
		if (tags[i] == tag) {
			tags.erase(tags.begin()+i);
			break;
		}
	}
}

bool BaseObject::HasTag(string tag)
{
	for (string currentTag : tags) {
		if (currentTag == tag)
			return true;
	}
	return false;
}

void BaseObject::AddComponent(BaseComponent* component)
{
	//if the component is a script it calls add script
	if (component->GetType() == SCRIPT)
		AddScript(component);
	//if not a script it is added ot the component vector
	else {
		if (components[component->GetType()] == nullptr)
			components[component->GetType()] = component;
		else 
			cout << "There is alreayd a " << ComponentTypeToString(component->GetType()) << " component on this object" << endl;
	}
}

BaseComponent* BaseObject::GetComponent(ComponentType type)
{
	//gets the component from the vector if it exists
	if (type < COMPONENT_COUNT)
		if (components[type] != nullptr)
			return components[type];

	return nullptr;
}

void BaseObject::HandleEvent(BaseEvent* event)
{
	//calls handle events for each component and script
	for (BaseComponent* component : components) {
		if(component != nullptr)
			component->HandleEvent(event);
	}
	for (BaseComponent* script : scripts) {
		script->HandleEvent(event);
	}
}



void BaseObject::PreRender()
{
	//updates all scrips and physics
	for (BaseComponent* script : scripts) {
		script->Update();
	}
	if (components[PHYSICS] != nullptr)
		components[PHYSICS]->Update();

	//scripts update
}

void BaseObject::Render()
{
	//updates sprite and text
	if (components[SPRITE] != nullptr)
		components[SPRITE]->Update();
	if (components[TEXT] != nullptr)
		components[TEXT]->Update();
}

void BaseObject::PostRender()
{
}

void BaseObject::DrawGui()
{
	//draws the name and tags to the inspector
	ImGui::Text("Name"); ImGui::SameLine();
	ImGui::InputText("    ", name, IM_ARRAYSIZE(name));

	for (auto tag : tags) {
		ImGui::Text(tag.c_str());
	}

	//calls draw gui of all components for component specific informaiton
	for (BaseComponent* component : components) {
		if(component != nullptr)
			component->DrawGui();
	}
	
}

void BaseObject::DrawHierarchy(ImGuiTreeNodeFlags flags)
{
	//makes a tree node for the current object
	bool isNodeOpen = ImGui::TreeNodeEx(name, flags, name);
	//checks if the item is clicked in the hierarchy
	if (ImGui::IsItemClicked())
		ObjectManager::GetInstance()->SetSelectedObject(this);
	
	if (ObjectManager::GetInstance()->GetSelectedObject() == this && ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("_TREENODE", this, sizeof(BaseObject*));
		ImGui::EndDragDropSource();
	}
	//checks if the object has had another object dropped onto it
	//this sets the parent of the object equal to this object
	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_TREENODE")) {
			if(ObjectManager::GetInstance()->GetSelectedObject() != nullptr)
				ObjectManager::GetInstance()->GetSelectedObject()->SetParent(this);
		}
		ImGui::EndDragDropTarget();
	}
	//draws the children of this object
	if (isNodeOpen) {
		for (BaseObject* child : children) {
			child->DrawHierarchy(flags);
		}
		ImGui::TreePop();
	}
}

void BaseObject::SetParent(BaseObject* parent_)
{
	//this is used to make sure that there is not a recursive loop due to a child in the hierarchy being set as the parent of one above it
	bool NonRecursive = true;
	BaseObject* currentParent = parent_;
	//makes sure the parent is not recursive (if the parent had this object set as its parent)
	while (currentParent != ObjectManager::GetInstance()->GetSceneRoots()[scene])
	{
		if (currentParent == this)
		{
			NonRecursive = false;
			break;
		}

		currentParent = currentParent->GetParent();
	}

	if (NonRecursive)
	{
		//removes the curent parent
		if (parent != ObjectManager::GetInstance()->GetSceneRoots()[scene] && parent != nullptr)
			RemoveParent();

		ObjectManager::GetInstance()->GetSceneRoots()[scene]->RemoveChild(this);
		//sets a new parent
		parent = parent_;
		parent->AddChild(this);
		
		((Transform*)GetComponent(TRANSFORM))->SetPosition(((Transform*)GetComponent(TRANSFORM))->GetLocalPosition() - ((Transform*)parent->GetComponent(TRANSFORM))->GetGlobalPos());
	}
}

void BaseObject::RemoveParent()
{
	//removes the parent and sets it to the scene root
	((Transform*)GetComponent(TRANSFORM))->SetPosition(((Transform*)GetComponent(TRANSFORM))->GetGlobalPos());
	parent->RemoveChild(this);
	parent = ObjectManager::GetInstance()->GetSceneRoots()[scene];
}

void BaseObject::RemoveChild(BaseObject* child)
{
	//checks if the child exists in the list of components and removes it
	for (int i = 0; i < children.size(); i++) {
		BaseObject* currentChild = children[i];
		if (currentChild == child) {
			children.erase(children.begin() + i);
		}
	}
}