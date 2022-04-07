#include "SDL.h"
#include <string>
#include <map>
#include <SDL_ttf.h>

using namespace std;
class ResourceManager {
private:
	/// Stores the instance of ResourceManager
	static ResourceManager* instance;

	/// A map storing image files
	map<string, SDL_Surface*>  imageFiles;
	/// A map storing font files
	map<string, TTF_Font*>  fontFiles;

public:
	/// This does not construct anyhting as the variables are by default constructed
	ResourceManager();
	/// This deletes any stored file in the map
	~ResourceManager();

	/// Gets the ResourceManager instance
	static ResourceManager* GetInstance();

	/// <summary>
	/// Checks if an image is already loaded, if not it is created
	/// 
	/// @warning The image type should be .bmp
	/// </summary>
	/// <param name="fileDirectory">the path to the image</param>
	/// <returns> the image that has been called for (either from the map or created)</returns>
	SDL_Surface* LoadImage(string fileDirectory);
	/// <summary>
	/// Checks if an font is already loaded, if not it is created
	/// 
	/// @warning The font type should be .ttf
	/// </summary>
	/// <param name="fileDirectory">the path to the image</param>
	/// <param name="fontSize">the size of the font</param>
	/// <returns> the font that has been called for (either from the map or created)</returns>
	TTF_Font* LoadFont(string fileDirectory, int fontSize = 15);

	/// removes the image from the map
	void UnloadImage(string fileDirectory);
	/// removes the font from the map
	void UnloadFont(string fileDirectory);
};
