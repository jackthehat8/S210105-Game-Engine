#pragma once
#include "BaseComponent.h"

class Sprite : 
    public BaseComponent
{
public:
    Sprite(const char* fileName, BaseObject* owner_, int renderLayer_ = 0,  bool useTransparency = false );

    void Update();
    void DrawGui();
    bool CheckClicked();

    void SetRenderLayer(int newLayer) { renderLayer = newLayer; }
    int GetRenderLayer() { return renderLayer; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }
    SDL_Texture* GetTexture() { return texture; }

    void Draw();
protected:
    SDL_Surface* surface;
    SDL_Texture* texture;

    int width = 0;
    int height = 0;

    int renderLayer = 0;
 
    SDL_Rect bounds;
};

