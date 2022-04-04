#pragma once
#include <vector>
#include "BaseObject.h"

using namespace std;

class SceneManager
{
public:
	/// <summary>
	/// adds an object to a scene (scenes start at 0)
	/// </summary>
	/// <param name="sceneNumber"></param>
	/// <param name="object"></param>
	void addObjectToScene(BaseObject* object, int sceneNumber = 0);

	/// <summary>
	/// sets the scene to be displayed (scenes start at 0)
	/// </summary>
	/// <param name="sceneNumber"></param>
	void setScene(int sceneNumber = 0);

	static SceneManager* GetInstance();
private:
	static SceneManager* instance;

	vector<vector<BaseObject*>> scenes;
};

