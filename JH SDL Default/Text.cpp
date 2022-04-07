#include "Text.h"
#include "ResourceManager.h"
#include "ScreenManager.h"
#include "Transform.h"

Text::Text(const char* fileName, int fontSize, BaseObject* owner_, string message_, SDL_Color colour_, Vector2f offset_) {
	type = TEXT;
	font = ResourceManager::GetInstance()->LoadFont(fileName, fontSize);//load the font from the resource manager
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
	//generate a surface
	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);

	if (!surface) {
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else {
		//generate the texture
		texture = SDL_CreateTextureFromSurface(ScreenManager::GetInstance()->getRenderer(), surface);
		if (!texture) {
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else {
			//render the texture on screen
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(ScreenManager::GetInstance()->getRenderer(), texture, NULL, &textRect);
		}
	}
	//destroy once renderd
	if (texture)
		SDL_DestroyTexture(texture);
	if (surface)
		SDL_FreeSurface(surface);
}

void Text::Update()
{
	//call update text
	UpdateText(message, ((Transform*)owner->GetComponent(TRANSFORM))->GetGlobalPos() + offset, font, colour);
}

void Text::DrawGUI()
{
	//display the message for the object
	if (ImGui::TreeNodeEx("Text", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text(("Message: " + message).c_str());
		ImGui::TreePop();
	}
}
