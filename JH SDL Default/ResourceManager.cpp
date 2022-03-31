#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = NULL;

ResourceManager::ResourceManager() {
};

ResourceManager::~ResourceManager() {
	//code from https://stackoverflow.com/questions/110157/how-to-retrieve-all-keys-or-values-from-a-stdmap-and-put-them-into-a-vector
	//removes the sdl_surface object from the heap
	for (map<string, SDL_Surface*>::iterator i = imageFiles.begin(); i!=imageFiles.end(); ++i)
	{
		delete (i->second);
	}
	imageFiles.clear();

	for (map<string, SDL_AudioSpec*>::iterator i = audioFiles.begin(); i != audioFiles.end(); ++i)
	{
		delete (i->second);
	}
	audioFiles.clear();

	for (map<string, TTF_Font*>::iterator i = fontFiles.begin(); i != fontFiles.end(); ++i)
	{
		delete (i->second);
	}
	fontFiles.clear();
	//end reference

	delete(this);
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

/// <summary>
/// Loads an audio file (.wav) into the heap or gets a reference to it if it already present.
/// </summary>
SDL_AudioSpec* ResourceManager::LoadAudio(string fileDirectory) {
	SDL_AudioSpec* newAudio = nullptr;
	Uint8* buf;
	Uint32 len;
	if (audioFiles.find(fileDirectory) == audioFiles.end()) {
		//SDL_LoadWAV(fileDirectory.c_str(), newAudio*, &buf, &len);
	}
	return newAudio;
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

void ResourceManager::UnloadAudio(string fileDirectory)
{
	delete(audioFiles.find(fileDirectory)->second);
	audioFiles.erase(audioFiles.find(fileDirectory));
}
