#pragma once
#include <vector>
#include "BaseObject.h"

using namespace std;

class SceneManager
{
public:
	/// adds an object to a scene (scenes start at 0)
	/// <param name="sceneNumber"></param>
	/// <param name="object"></param>
	void addObjectToScene(BaseObject* object, int sceneNumber = 0);

	/// sets the scene to be displayed (scenes start at 0)
	/// <param name="sceneNumber"></param>
	void setScene(int sceneNumber = 0);

	/// Gets the instance of the SceneManager
	static SceneManager* GetInstance();

private:
	/// Stores the instance of the SceneManager
	static SceneManager* instance;

	/// a vector of scenes
	vector<vector<BaseObject*>> scenes;
};

