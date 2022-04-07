#include "Game.h"
#undef main
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>
#include "Window Constants.h"


/*
TO DO
-make a point all gameobjects have local positions to allow scrolling

-find sprites to make game with

code to comment
	game object
	input manager.h
	system
	events
	physics
*/
int main(int argc, char* argv[])
{
	bool quit = false;
	int r = 50;
	int g = 50;
	int b = 50;
	Game* game = new Game();
	ScreenManager::GetInstance()->SetDisplayColour(r % 255, g % 255, b % 255, 255);

	while (!quit&& game) {
		quit = game->Update();
	}
	game->~Game();
	return 0;
}