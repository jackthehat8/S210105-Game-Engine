#include <SDL.h>
#include "Window Constants.h"
class ScreenManager
{
private:
	/// stores the instance of the ScreenManager
	static ScreenManager* instance;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
public:

	/// Gets the instanec of the ScreenManager
	static ScreenManager* GetInstance();
	/// <summary>
	/// This creates the window
	/// 
	/// THis creats a SDL_Window and a SDL_Renderer
	/// </summary>
	/// <param name="x">The x position for the window to be generated from</param>
	/// <param name="y">The y position for the window to be generated from</param>
	/// <param name="width">The width of the window</param>
	/// <param name="height">The height of the window</param>
	ScreenManager(int x = WindowStartX, int y = WindowStartY, int width = ScreenWidth, int height = ScreenHeight);
	///This deletes the window and render
	~ScreenManager();

	/// This sets the background of the window
	/// <param name="red"></param>
	/// <param name="green"></param>
	/// <param name="blue"></param>
	/// <param name="alpha"></param>
	void SetDisplayColour(int, int, int, int);
	/// returns the SDL_Window
	SDL_Window* getWindow() { return m_window; }
	/// returns the SDL_Renderer
	SDL_Renderer* getRenderer() { return m_renderer; }
};

