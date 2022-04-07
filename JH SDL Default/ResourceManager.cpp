#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager() {
};

ResourceManager::~ResourceManager() {
	imageFiles.clear();
	fontFiles.clear();
}

ResourceManager* ResourceManager::GetInstance()
{
	//creates a new Screen Manager class if ones does not exist to be referenced to
	if (instance == NULL)
		instance = new ResourceManager();
	return instance;
}

/// <summary>
/// Loads an image (.bmp) into the heap or gets a reference to it if it already present.
/// </summary>
SDL_Surface* ResourceManager::LoadImage(string fileDirectory) {
	//make a new surface for the image to be loaded into
	SDL_Surface* newSurface = nullptr;
	//checks if the image exists in the map
	if (imageFiles.find(fileDirectory) == imageFiles.end()) {
		//if it doesnt exist create it and store it in the map
		newSurface = SDL_LoadBMP(fileDirectory.c_str());
		imageFiles.insert(pair<string, SDL_Surface*>(fileDirectory, newSurface));
	}
	else {
		//get the image form the map if present
		newSurface = imageFiles.find(fileDirectory)->second;
	}

	return newSurface;
}

/// <summary>
/// Loads an font (.ttf) into the heap or gets a reference to it if it already present.
/// </summary>
TTF_Font* ResourceManager::LoadFont(string fileDirectory, int fontSize)
{
	string tempDirectory = fileDirectory + to_string(fontSize);
	TTF_Font* newFont = nullptr;
	if (fontFiles.find(tempDirectory) == fontFiles.end()) {
		newFont = TTF_OpenFont(fileDirectory.c_str(), fontSize);
		fontFiles.insert(pair<string, TTF_Font*>(tempDirectory, newFont));
	}
	else {
		newFont = fontFiles.find(tempDirectory)->second;
	}
	return newFont;
};

void ResourceManager::UnloadImage(string fileDirectory) {
	delete(imageFiles.find(fileDirectory)->second);
	imageFiles.erase(imageFiles.find(fileDirectory));
}

void ResourceManager::UnloadFont(string fileDirectory)
{
	delete(fontFiles.find(fileDirectory)->second);
	fontFiles.erase(fontFiles.find(fileDirectory));
}
