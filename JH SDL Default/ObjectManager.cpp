#include "ObjectManager.h"

#include <iostream>
#include "BaseObject.h"

#include "Game.h"

#include "Sprite.h"

ObjectManager* ObjectManager::instance = NULL;
BaseObject* ObjectManager::sceneRoot = new BaseObject("Scene Root");

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

ObjectManager* ObjectManager::GetInstance()
{
    //creates a new objectManager class if ones does not exist to be referenced to
    if (instance == NULL)
        instance = new ObjectManager();
    return instance;
}

void ObjectManager::PreRender()
{
}

void ObjectManager::Render()
{
}

void ObjectManager::PostRender()
{
}

bool ObjectManager::CheckIfClicked()
{
    return false;
}

void ObjectManager::DrawGui()
{
    
}

void ObjectManager::OnMouseDown()
{
}

void ObjectManager::OnMouseHeld()
{
}

void ObjectManager::OnMouseUp()
{
}

void ObjectManager::SetSelectedObject(BaseObject* object)
{
    selectedObject = object;
}

void ObjectManager::SetHeldObject(BaseObject* object)
{
    heldObject = object;
}

void ObjectManager::sortObjects()
{
    vector<BaseObject*> spriteUpdates;
    vector<BaseObject*> otherUpdates;
    for (BaseObject* object : objects) {
        if (object->GetComponent(SPRITE) != nullptr) 
            spriteUpdates.push_back(object);
        else
            otherUpdates.push_back(object);
    }
    spriteUpdates = QuickSort(spriteUpdates, 0, spriteUpdates.size() - 1);
    for (BaseObject* object : spriteUpdates) {
        otherUpdates.push_back(object);
    }
    objects = otherUpdates;
}

std::vector<BaseObject*> ObjectManager::QuickSort(std::vector<BaseObject*> input, int first, int last)
{
    if (first < last)
    {
        int pivotValue = ((Sprite*)(input[first]->GetComponent(SPRITE)))->GetRenderLayer();
        int leftPointer = first;
        int rightPointer = last;

        while (leftPointer < rightPointer)
        {
            while (((Sprite*)(input[leftPointer]->GetComponent(SPRITE)))->GetRenderLayer() <= pivotValue && leftPointer <= rightPointer && leftPointer < last)
            {
                leftPointer++;
            }
            while (((Sprite*)(input[rightPointer]->GetComponent(SPRITE)))->GetRenderLayer() >= pivotValue && rightPointer >= leftPointer && rightPointer > first)
            {
                rightPointer--;
            }
            if (leftPointer < rightPointer)
            {
                BaseObject* temp = input[leftPointer];
                input[leftPointer] = input[rightPointer];
                input[rightPointer] = temp;
            }
        }

        int pivot = rightPointer;
        BaseObject* temp1 = input[first];
        input[first] = input[pivot];
        input[pivot] = temp1;

        input = QuickSort(input, first, pivot - 1);
        input = QuickSort(input, pivot + 1, last);
    }
    return input;
}

/// <summary>
/// runs  pre-render, render and post-render of each object
/// </summary>
void ObjectManager::Update()
{

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->PreRender();
	}

    sortObjects();

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Render();
    }

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->PostRender();
    }

    //imgui display

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->GetComponent(SPRITE) != nullptr && ((Sprite*)objects[i]->GetComponent(SPRITE))->CheckClicked())
            break;
    }

    if (instance->selectedObject != nullptr && Game::GetInstance()->getGUIVisable())
        instance->selectedObject->DrawGui();
    if (!ImGui::GetIO().MouseDown[0])
        instance->heldObject = nullptr;
    if (instance->heldObject != nullptr)
        instance->heldObject->OnMouseHeld();
}

void ObjectManager::AddObject(BaseObject* object)
{
	objects.push_back(object);
}

void ObjectManager::AddRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

const char* ObjectManager::ComponentTypeToString(ComponentType type)
{
    switch (type) {
    case TRANSFORM:
        return "TRANSFORM";
    case SPRITE:
        return"SPRITE";
    case AUDIO:
        return "AUDIO";
    case TEXT:
        return "TEXT";
    case PHYSICS:
        return "PHYSICS";
    }
    return "";
}
