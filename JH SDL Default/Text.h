#pragma once
#include "BaseComponent.h"
#include <string>
#include <SDL_ttf.h>

/// this is used to display text onto the screen
/// 
/// it can be paired with a sprite on the samae BaseObject to add a background behind the text
class Text :
    public BaseComponent
{
public:
    /// <summary>
    /// This loads the font that is input
    /// </summary>
    /// <param name="fileName">the address that the .ttf file is</param>
    /// <param name="fontSize">the size the font wants to be</param>
    /// <param name="owner_">the BaseObject that the component is to be added onto</param>
    /// <param name="message_">the message to be displayed</param>
    /// <param name="colour_">the colour the font should be</param>
    /// <param name="offset_">a possible offset that can be added to centre it on a background if needed
    /// @note this is defaulted to 0,0 </param>
    ///
    /// Example
    /// ~~~~~.cpp
    /// BaseObject* tempObject = new BaseObject("temp", 550, 275, 0);
    /// tempObject->AddComponent(new Text("assets/temp.ttf", 100, tempObject, "this is a temporary message", { 0,0,0 }, { 125,50 }));
    /// ~~~~~
    Text(const char* fileName, int fontSize, BaseObject* owner_, string message_, SDL_Color colour_, Vector2f offset_ = {0,0});

    /// allows for the message to be updated
    /// <param name="message_">the new message to be displayed</param>
    void SetMessage(string message_) { message = message_; }

    /// This draws the message to the screen
    /// <param name="msg">the message to be displayed</param>
    /// <param name="x">The x position to display at</param>
    /// <param name="y">The y position to display at</param>
    /// <param name="font">the font to use</param>
    /// <param name="colour">the colour to make the text</param>
    void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);

    /// his draws the message to the screen
    /// <param name="msg">the message to be displayed</param>
    /// <param name="pos">the positon to display at</param>
    /// <param name="font">the font to use</param>
    /// <param name="colour">the colour to make the text</param>
    void UpdateText(string msg, Vector2f pos, TTF_Font* font, SDL_Color colour) { UpdateText(msg, pos.x, pos.y, font, colour); }

    /// <summary>
    /// runs UpdateText with values that are saved from the constructor
    /// </summary>
    void Update();

    /// displays the message in the inspector
    void DrawGUI();

private:
    /// message to display
    string message;
    /// value to offset by
    Vector2f offset;
    /// font to use (with the size it should be)
    TTF_Font* font;
    /// the colour the font should be
    SDL_Color colour;
};

