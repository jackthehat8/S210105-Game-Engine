#include "Text.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Transform.h"

Text::Text(const char* fileName, int fontSize, BaseObject* owner_, string message_, SDL_Color colour_, Vector2f offset_) {
	type = TEXT;
	font = ResourceManager::GetInstance()->LoadFont(fileName, fontSize);
	message = message_;
	colour = colour_;
	offset = offset_;
	owner = owner_;
}

void Text::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour)
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);

	if (!surface) {
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else {
		texture = SDL_CreateTextureFromSurface(ScreenManager::GetInstance()->getRenderer(), surface);
		if (!texture) {
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else {
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(ScreenManager::GetInstance()->getRenderer(), texture, NULL, &textRect);
		}
	}
	if (texture)
		SDL_DestroyTexture(texture);
	if (surface)
		SDL_FreeSurface(surface);
}

void Text::Update()
{
	UpdateText(message, ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos() + offset, font, colour);
}
