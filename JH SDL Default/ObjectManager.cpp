#include "ObjectManager.h"
#include <iostream>
#include "BaseObject.h"
#include "Game.h"
#include "Quit.h"
#include "Sprite.h"
#include "Profiler.h"

ObjectManager* ObjectManager::instance = NULL;

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
    //sorts objects that have a render layer from Sprite
    //any other object is put onto the end of the update vector
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
    //runs preRender, render and postRender of each object
    profileSample* update = new profileSample("Update Objects");

    profileSample* preRender = new profileSample("PreRender");
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->PreRender();
	}
    preRender->EndSample();

    profileSample* render = new profileSample("Render");
    sortObjects();

    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->Render();
    }
    render->EndSample();

    profileSample* postRender = new profileSample("Update Objects");
    for (int i = 0; i < objects.size(); i++)
    {
        objects[i]->PostRender();
    }
    postRender->EndSample();

    profileSample* objIMGUI = new profileSample("Object IMGUI");
    //imgui display
    if (Game::GetInstance()->getGUIVisable()) {
        ImGui::Begin("Inspector");
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->GetComponent(SPRITE) != nullptr && ((Sprite*)objects[i]->GetComponent(SPRITE))->CheckClicked())
                break;
        }

        if (instance->selectedObject != nullptr)
            instance->selectedObject->DrawGui();
        if (!ImGui::GetIO().MouseDown[0])
            instance->heldObject = nullptr;
        if (instance->heldObject != nullptr)
            instance->heldObject->OnMouseHeld();
        ImGui::End();
    }
    objIMGUI->EndSample();
    update->EndSample();
}

void ObjectManager::AddObject(BaseObject* object)
{
	objects.push_back(object);
}

const char* ObjectManager::ComponentTypeToString(ComponentType type)
{
    //converts the component type to a string
    switch (type) {
    case TRANSFORM:
        return "TRANSFORM";
    case SPRITE:
        return"SPRITE";
    case TEXT:
        return "TEXT";
    case PHYSICS:
        return "PHYSICS";
    }
    return "";
}

void ObjectManager::AddSceneRoot()
{
    //creats a new scene root and pushes it back to Scene Root
    BaseObject* newSceneRoot = new BaseObject("Scene Root");
    newSceneRoot->AddComponent(new Quit(newSceneRoot));
    sceneRoots.push_back(newSceneRoot);
}
