#include "ScreenManager.h"
#include <stdio.h>

ScreenManager* ScreenManager::instance = NULL;

ScreenManager* ScreenManager::GetInstance()
{
	//creates a new Screen Manager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new ScreenManager();
	return instance;
}

ScreenManager::ScreenManager(int x, int y, int width, int height) {
	m_window = nullptr;
	m_renderer = nullptr;

	m_window = SDL_CreateWindow(
		"A Window", //title
		x, //start x
		y, //start y
		width, //width
		height, //height
		0 //behavior flags
	);

	if (!m_window) {
		printf("WINDOW initialsation failed %s\n", SDL_GetError());
		printf("Press any key to continue\n");;
		getchar();
		return;
	}

	m_renderer = SDL_CreateRenderer(
		m_window, //link to window
		-1, //index rendering driver
		0 //behavior flags
	);

	if (!m_renderer) {
		printf("RENDERER initialsation failed %s\n", SDL_GetError());
		printf("Press any key to continue\n");;
		getchar();
		return;
	}
}

ScreenManager::~ScreenManager() {
	if (m_renderer) {
		SDL_DestroyRenderer(m_renderer);
	}
	if (m_window) {
		SDL_DestroyWindow(m_window);
	}
	delete(this);
}

/// <summary>
/// sets the colour of the screen
/// </summary>
void ScreenManager::SetDisplayColour(int r, int g, int b, int a = 255) {
	if (m_renderer) {
		int result = SDL_SetRenderDrawColor(
			m_renderer, //renderer
			r, //r
			g, //g
			b, //b
			a //alpha
		);
	}
}