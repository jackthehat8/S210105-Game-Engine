#include "Game.h"
#undef main
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>
#include "Window Constants.h"

int main(int argc, char* argv[])
{
	bool quit = false;
	//the main game is built through the Game class
	Game* game = new Game();
	ScreenManager::GetInstance()->SetDisplayColour(50, 50,50, 255);

	while (!quit&& game) {
		quit = game->Update();
	}
	game->~Game();
	return 0;
}