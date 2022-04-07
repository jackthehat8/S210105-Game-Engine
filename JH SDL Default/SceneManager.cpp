#include "SceneManager.h"
#include "ObjectManager.h"
#include <cstddef>

SceneManager* SceneManager::instance = NULL;

void SceneManager::addObjectToScene(BaseObject* object, int sceneNumber)
{
    if (object->GetName() != "Scene Root") {
        //gives each the scene root and creates empty scenes to the one trying to be added to
        while (scenes.size() < sceneNumber + 1) {
            vector<BaseObject*> temp;
            ObjectManager::GetInstance()->AddSceneRoot();
            temp.push_back(ObjectManager::GetInstance()->GetSceneRoots()[scenes.size()]);
            scenes.push_back(temp);
        }
        //add to the scene being displayed if added to it
        if (sceneNumber == ObjectManager::GetInstance()->currentScene) {
            ObjectManager::GetInstance()->AddObject(object);
        }
        //add to stored scene
        scenes[sceneNumber].push_back(object);
    }
}


void SceneManager::setScene(int sceneNumber)
{
    //sets the scene to the input number if it exists
    if (sceneNumber < scenes.size()) {
        ObjectManager::GetInstance()->SetScene(scenes[sceneNumber], sceneNumber);
    }
}

SceneManager* SceneManager::GetInstance()
{
     if (instance == NULL)
         instance = new SceneManager();
    return instance;
}
