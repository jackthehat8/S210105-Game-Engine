#include "BaseObject.h"
#include <iostream>
#include "Transform.h"
#include "BaseComponent.h"
#include "BaseScript.h"
#include "SceneManager.h"

BaseObject::BaseObject(const char* name_, int x, int y, int sceneNumber)
{
	
	Transform* temp = new Transform(Vector2f(x, y), this);
	AddComponent(temp);
	scene = sceneNumber;
	if (name_ != "Scene Root") {
		SceneManager::GetInstance()->addObjectToScene(this, sceneNumber);
		SetParent(ObjectManager::GetInstance()->GetSceneRoots()[scene]);
	}
	name = (char*)name_;
}

void BaseObject::OnMouseHeld()
{
	Transform* transform = (Transform*)components[TRANSFORM];
	if (parent == nullptr)
		transform->SetPosition(Vector2f(transform->GetLocalPosition().x + ImGui::GetIO().MouseDelta.x, 
			transform->GetLocalPosition().y + ImGui::GetIO().MouseDelta.y));
	else {
		Vector2f globalPos = transform->GetGlobalPos();
		globalPos.x += ImGui::GetIO().MouseDelta.x;
		globalPos.y += ImGui::GetIO().MouseDelta.y;

		transform->SetPosition(globalPos - ((Transform*)(parent->GetComponent(TRANSFORM)))->GetGlobalPos());
	}
}

void BaseObject::AddTag(string tag)
{
	bool exists = false;
	for (string currentTag : tags)
	{
		if (tag == currentTag) {
			exists = true;
			break;
		}
	}

	if (!exists)
		tags.push_back(tag);
}

void BaseObject::RemoveTag(string tag)
{
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
	if (component->GetType() == SCRIPT)
		AddScript(component);
	else {
		if (components[component->GetType()] == nullptr)
			components[component->GetType()] = component;
		else 
			cout << "There is alreayd a " << ComponentTypeToString(component->GetType()) << " component on this object" << endl;
	}
}

BaseComponent* BaseObject::GetComponent(ComponentType type)
{
	if (type < COMPONENT_COUNT)
		if (components[type] != nullptr)
			return components[type];
		/*else
			cout << "No Component of " << ComponentTypeToString(type) << " exists on " << name << endl;
	else
		cout << ComponentTypeToString(type) << " is outside of the range of the array (if script use GetScript)" << endl;*/

	return nullptr;
}

void BaseObject::HandleEvent(BaseEvent* event)
{
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
	for (BaseComponent* script : scripts) {
		script->Update();
	}
	if (components[PHYSICS] != nullptr)
		components[PHYSICS]->Update();

	//scripts update
}

void BaseObject::Render()
{
	if (components[SPRITE] != nullptr)
		components[SPRITE]->Update();
	if (components[AUDIO] != nullptr)
		components[AUDIO]->Update();
	if (components[TEXT] != nullptr)
		components[TEXT]->Update();
}

void BaseObject::PostRender()
{
}

void BaseObject::DrawGui()
{
	ImGui::Begin("Inspector");
	ImGui::Text("Name"); ImGui::SameLine();
	ImGui::InputText("    ", name, IM_ARRAYSIZE(name));

	for (BaseComponent* component : components) {
		if(component != nullptr)
			component->DrawGui();
	}

	ImGui::End();
	
}

void BaseObject::DrawHierarchy(ImGuiTreeNodeFlags flags)
{
	if (ImGui::TreeNodeEx(name, flags, name)) {
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

		if (parent != ObjectManager::GetInstance()->GetSceneRoots()[scene] && parent != nullptr)
			RemoveParent();

		parent = parent_;
		parent->AddChild(this);
		
		((Transform*)GetComponent(TRANSFORM))->SetPosition(((Transform*)GetComponent(TRANSFORM))->GetLocalPosition() - ((Transform*)parent->GetComponent(TRANSFORM))->GetGlobalPos());
	}
	/*else {
		printf("Tried to set parent as one of its children which would make a recursive loop");
	}*/
	//ADD AN ELSE FOR ERROR CHECKING FOR MAKING A PARENT OF ITSELF (like above)
}

void BaseObject::RemoveParent()
{
	((Transform*)GetComponent(TRANSFORM))->SetPosition(((Transform*)GetComponent(TRANSFORM))->GetGlobalPos());
	parent->RemoveChild(this);
	SetParent(ObjectManager::GetInstance()->GetSceneRoots()[scene]);
}

void BaseObject::RemoveChild(BaseObject* child)
{
	for (int i = 0; i < children.size(); i++) {
		BaseObject* currentChild = children[i];
		if (currentChild == child) {
			children.erase(children.begin() + i);
		}
	}
}