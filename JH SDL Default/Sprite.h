#pragma once
#include "BaseComponent.h"

class Sprite : 
    public BaseComponent
{
public:
    /// creates the surface and texture for the sprite
    /// <param name="fileName">the address that the .bmp file is</param>
    /// <param name="owner_">the BaseObject that the component is to be added onto</param>
    /// <param name="renderLayer_">the layer for the sprite to be rendered on</param>
    /// <param name="useTransparency">if the sprite should remove the background 
    /// @note for this to work the background should be the colour {255,255,0,0}</param>
    Sprite(const char* fileName, BaseObject* owner_, int renderLayer_ = 0,  bool useTransparency = false );

    /// Calls draw
    ///
    /// if visability is set to false it will not draw the sprite to the screen
    void Update();

    /// Writes the render layer to the inspector
    void DrawGui();

    /// checks if the user has clicked the sprite to set it as the selectedObject in the ObjectManager
    bool CheckClicked();

    /// sets the renderLayer to the new value 
    /// 
    /// @note the lower the number the further back into the scene it will be
    void SetRenderLayer(int newLayer) { renderLayer = newLayer; }

    /// gets the render layer of the sprite
    int GetRenderLayer() { return renderLayer; }

    /// gets the width of the sprite
    int GetWidth() { return width; }
    /// gets the height of the sprite
    int GetHeight() { return height; }

    /// gets the sprite texture
    /// 
    /// this is mostly used for the content window 
    SDL_Texture* GetTexture() { return texture; }

    /// gets the current visability of the sprite
    bool GetVisability() { return visable; }

    /// sets the visability of the sprite
    void SetVisability(bool newVisability) { visable = newVisability; }

    /// draws the texutre to the screen
    /// 
    /// this uses the Transform component to get a position to draw at 
    /// @note if the tools are visable it will add a red collison box to the outside of the sprite to show where it would collide/overlap with the physics system
    void Draw();
protected:
    /// the surface that is generated for the sprite
    SDL_Surface* surface;
    /// the texture that is generated for the sprite
    SDL_Texture* texture;

    /// the width of the sprite
    int width = 0;
    /// the height of the sprite
    int height = 0;
    /// the render layer of the sprite
    int renderLayer = 0;

    /// the visabiity of the sprite
    bool visable = true;
};

