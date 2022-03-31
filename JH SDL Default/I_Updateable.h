#pragma once
#include "SDL.h"
#include <vector>
class I_Updateable
{
private:
	std::vector<I_Updateable*> updates;
	SDL_Renderer* m_renderer;
public:
	I_Updateable();
	~I_Updateable();
	virtual void Update();
	void AddObjects(I_Updateable* object);
	void AddRenderer(SDL_Renderer* renderer);
};

