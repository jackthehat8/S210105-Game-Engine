#include "I_Updateable.h"


I_Updateable::I_Updateable()
{
}

I_Updateable::~I_Updateable()
{
}

void I_Updateable::Update()
{

	for (int i = 0; i < updates.size(); i++)
	{
		updates[i]->Update();
	}
	SDL_RenderPresent(m_renderer);
}

void I_Updateable::AddObjects(I_Updateable* object)
{
	updates.push_back(object);
}

void I_Updateable::AddRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
