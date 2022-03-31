#include "InputManager.h"
#include "EventManager.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl.h>
#include <imgui_sdl.h>
#include <imgui_internal.h>

Input* Input::instance = NULL;

Input::Input()
{
	eventManager = EventManager::GetInstance();
}

Input::~Input() {

}

Input* Input::GetInstance()
{
	//creates a new Screen Manager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new Input();
	return instance;
}

/// <summary>
/// checks to see if any key has been pressed and will make a new event if true
/// </summary>
void Input::Update() {
	SDL_Event m_event;
	while (SDL_PollEvent(&m_event) != NULL) {
		if (m_event.type == SDL_QUIT)
			eventManager->QueueEvent(new QuitEvent());
		//code from https://skia.googlesource.com/external/github.com/ocornut/imgui/+/refs/tags/v1.65/examples/imgui_impl_sdl.cpp
		else if (m_event.type == SDL_TEXTINPUT)
		{
			ImGui::GetIO().AddInputCharactersUTF8(m_event.text.text); //used for keyinput for imgui
		}
		//end of referenced code
		else if (m_event.type == SDL_KEYDOWN) {
			SDL_Keycode keyPressed = m_event.key.keysym.sym;
			
			switch (keyPressed) 
			{
			case SDLK_ESCAPE:
				eventManager->QueueEvent(new EscapeInput(true));
				break;
			case SDLK_w:
			case SDLK_SPACE:
				eventManager->QueueEvent(new UpInput(true));
				break;
			case SDLK_a:
				eventManager->QueueEvent(new LeftInput(true));
				break;
			case SDLK_d:
				eventManager->QueueEvent(new RightInput(true));
				break;
			case SDL_MOUSEBUTTONDOWN == SDL_BUTTON_LEFT:
				int x;
				int y;
				SDL_GetMouseState(&x, &y);
				eventManager->QueueEvent(new LMBInput(true, x, y));
				break;
			}
		}
		else if (m_event.type == SDL_KEYUP) {
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch (keyPressed) 
			{
			case SDLK_w:
			case SDLK_SPACE:
				eventManager->QueueEvent(new UpInput(false));
				break;
			case SDLK_a:
				eventManager->QueueEvent(new LeftInput(false));
				break;
			case SDLK_d:
				eventManager->QueueEvent(new RightInput(false));
				break;
			}
		}
	}
}