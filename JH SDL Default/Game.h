#ifndef GAME_H
#define GAME_H
#include "System.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Physics.h"
#include "Constants.h"
#include <stdio.h>
#include <string>

#include <filesystem>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>

using namespace std;

struct IMGUISprite {
	Sprite* sprite;
	string name;

	IMGUISprite(string name_, Sprite* sprite_) {
		name = name_;
		sprite = sprite_;
	}
};

struct FrameQueue {
public:
	vector<float> queue;
	int maxFrames = 300;

	void pushFrame(float newFrame) {
		int difference = queue.size() - maxFrames;

		for (int i = -1; i < difference; i++)
		{
			queue.erase(queue.begin());
		}

		queue.push_back(newFrame);
	}

	float GetAverage() {
		float count = 0;
		for (int i = 0; i < queue.size(); i++)
		{
			count += queue[i];
		}
		return count / queue.size();
	}
};

class Game {
private:
	System* mainSystem;

	ScreenManager* screen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	ObjectManager* updates;

	ResourceManager* resourceManager;

	BaseObject* monster;
	BaseObject* monsterTrans;
	BaseObject* monsterTransKeyed;
	BaseObject* floor;
	BaseObject* startWall;
	BaseObject* endWall;

	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont;

	FrameQueue frames;

	vector<IMGUISprite*> directoryContent;

	bool GUIVisable = true;

	static Game* instance;
public:
	Game();
	~Game();

	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);

	void Update(void);

	void Delay(Uint32);

	void SearchDirectory();

	ScreenManager* GetScreenManager();

	static Game* GetInstance();

	bool getGUIVisable() { return GUIVisable; }
};

#endif