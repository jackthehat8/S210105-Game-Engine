#ifndef GAME_H
#define GAME_H
#include "System.h"
#include "Sprite.h"
#include "Physics.h"
#include "Window Constants.h"
#include <stdio.h>
#include <string>

#include <filesystem>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>

using namespace std;

/// <summary>
/// This is used to store sprites for the ImGui Content Window
/// </summary>
struct IMGUISprite {
	Sprite* sprite;
	string name;

	IMGUISprite(string name_, Sprite* sprite_) {
		name = name_;
		sprite = sprite_;
	}
};

/// <summary>
/// This is used for storing the previous 300 frames for the performance window
/// </summary>
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

/// Constructs the game and runs the main loop
/// This is a singleton as there should only be one per game
class Game {
private:

	/// The frames that are stored for use in the Performance window
	FrameQueue frames;

	/// The storage for an example of each asset found in the asset folder
	/// This is used in the Content window (found inside the Editor window)
	vector<IMGUISprite*> directoryContent;

	/// Stores the content being dragged from the Content window
	IMGUISprite* contentBeingDragged = nullptr;

	/// Used to turn the tools on and off
	bool GUIVisable = true;

	/// Used to exit the loop when set to true
	bool quit = false;

	/// Stores the instance of the game
	static Game* instance;

public:
	/// Set up the back end of the game
	/// 
	/// First it creates System
	/// Next it calls LoadLevels to load the BaseObject(s) of the game
	/// ImGui is also initialised
	Game();

	/// Calls deconstruct of the System
	~Game();

	/// This is the main loop of the game
	/// 
	/// This first starts a new frame for Profiler, Time and ImGui
	/// The InputManager is called to poll for any inputs happening this frame
	/// Next it fires the events that are stored in the EventManager
	/// After this it calls Update in the ObjectManager 
	/// If tools are set to be shown; DrawPerformanceWindow, DrawEditorWindow and DrawHierarchyWindow are then called to show the tools on screen
	/// Once these have been completed the frame is ended
	/// @returns A value is returned to say if the game was told to quit in the frame, this can then be handled in main
	bool Update();

	/// This is used to produce a list of assets stored in the asset folder of the program
	/// This list is used in the content window to display possible assets
	void SearchDirectory();

	/// This allows the instance of Game Object to be retrieved
	/// 
	/// <returns>The instance of Game</returns>
	static Game* GetInstance();

	/// Gets the visability of the tools
	/// 
	/// <returns>The state of GUIVisable</returns>
	bool getGUIVisable() { return GUIVisable; }

	/// Sets quit to true to allow the loop to stopped
	void Quit() { quit = true; }

	/// Loads the BaseObjects of the game to be rendered in thier scenes
	void LoadLevels();

	/// Draws the Performance window and its tool(s)
	void DrawPerformanceWindow();
	/// Draws the Editor window and its tool(s)
	void DrawEditorWindow();
	/// Draws the Hierarchy window and its tool(s)
	void DrawHierarchyWindow();
};

#endif