#pragma once
#include "BaseComponent.h"
#include <string>
#include <SDL_ttf.h>

class Text :
    public BaseComponent
{
public:
    Text(const char* fileName, int fontSize, BaseObject* owner_, string message_, SDL_Color colour_, Vector2f offset_ = {0,0});

    void SetMessage(string message_) { message = message_; }

    void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
    void UpdateText(string msg, Vector2f pos, TTF_Font* font, SDL_Color colour) { UpdateText(msg, pos.x, pos.y, font, colour); }

    void Update();

private:
    string message;

    Vector2f offset;
    TTF_Font* font;
    SDL_Color colour;
};

