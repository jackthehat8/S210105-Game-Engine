#include <SDL.h>
#include "Constants.h"
class ScreenManager
{
private:

	static ScreenManager* instance;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
public:

	static ScreenManager* GetInstance();
	ScreenManager(int x = WindowStartX, int y = WindowStartY, int width = ScreenWidth, int height = ScreenHeight);
	~ScreenManager();
	void SetDisplayColour(int, int, int, int);
	SDL_Window* getWindow() { return m_window; }
	SDL_Renderer* getRenderer() { return m_renderer; }
};

