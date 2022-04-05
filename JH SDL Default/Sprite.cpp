#include "Sprite.h"
#include "Vector.h"
#include "Transform.h"
#include "Game.h"

Sprite::Sprite(const char* fileName, BaseObject* owner_, int renderLayer_, bool useTransparency)
{
	owner = owner_;
	type = SPRITE;
	renderLayer = renderLayer_;
	surface = ResourceManager::GetInstance()->LoadImage(fileName);
	if (!surface) {
		printf("SURFACE fro bitmap %s not loaded\n", fileName);
		printf("%s\n", SDL_GetError());
	}
	else {
		if (useTransparency) {
			Uint32 colourKey = SDL_MapRGB(surface->format, 255, 0, 255);
			SDL_SetColorKey(surface, SDL_TRUE, colourKey);
		}

		texture = SDL_CreateTextureFromSurface(ScreenManager::GetInstance()->getRenderer(), surface);
		if (!texture) {
			printf("TEXTURE for bitmap %s not loaded\n", fileName);
			printf("%s\n", SDL_GetError());
		}
		else {
			width = surface->w;
			height = surface->h;
		}
	}
	bounds.x = 0;
	bounds.y = 0;
	bounds.w = width;
	bounds.h = height;
	
}

void Sprite::Update()
{
	if(visable)
		Draw();
}



void Sprite::DrawGui()
{
	ImGui::Text("Render Layer");
	ImGui::SameLine(); ImGui::InputInt("",&renderLayer, 1);		
}

void Sprite::Draw()
{
	Transform* transform = (Transform*)(owner->GetComponent(TRANSFORM));
	if (texture&& surface&& transform != nullptr) {
		Vector2f temp = transform->GetGlobalPos();
		SDL_Rect destRect = { temp.x,temp.y,surface->w,surface->h };
		SDL_RenderCopy(ScreenManager::GetInstance()->getRenderer(), texture, NULL, &destRect);
		if (Game::GetInstance()->getGUIVisable()) {
			SDL_SetRenderDrawColor(ScreenManager::GetInstance()->getRenderer(), 255, 0, 0, 255);
			SDL_RenderDrawRect(ScreenManager::GetInstance()->getRenderer(), &destRect);
			SDL_SetRenderDrawColor(ScreenManager::GetInstance()->getRenderer(), 50, 50, 50, 255);
		}
	}
	
}


bool Sprite::CheckClicked()
{
	SDL_Point mouseLocation;

	mouseLocation.x = ImGui::GetIO().MousePos.x;
	mouseLocation.y = ImGui::GetIO().MousePos.y;

	Vector2f tempPos = ((Transform*)(owner->GetComponent(TRANSFORM)))->GetGlobalPos();

	SDL_Rect spriteRect = { tempPos.x, tempPos.y, surface->w, surface->h };

	if (SDL_PointInRect(&mouseLocation, &spriteRect) && ImGui::GetIO().MouseClicked[0])
	{
		ObjectManager::GetInstance()->SetSelectedObject(owner);
		ObjectManager::GetInstance()->SetHeldObject(owner);
		return true;
	}

	return false;
}